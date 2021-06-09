#include <iostream>
#include <vector>
#include "data_utils.h"
#include "consts.h"
#include "module.h"
#include "optim.h"
#include <cstdlib>
#include<chrono>
#include <ctime>
using namespace  std;
int main() {
    srand(time(NULL));
    vector<MyData> data = read_data(DATAFILE);
    for (auto c: data){
        c.output();
    }
    map<string, int> mm = read_names(data);
    for(auto c:mm){
        cout << c.first << " " << c.second << endl;
    }
    auto p = getdataxy(data, mm);
    for(int i =0;i<p.first.size();++i){
        for(auto d:p.first[i]){
            cout << d << " ";
        }
        cout << p.second[i];
        cout << endl;
    }
    normalize(p.first);
    for(int i =0;i<p.first.size();++i){
        for(auto d:p.first[i]){
            cout << d << " ";
        }
        cout << p.second[i];
        cout << endl;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine A_RANDOM_ENGINE(seed);
    Linear dense1(4, 5, A_RANDOM_ENGINE);
    Linear dense2(5,5, A_RANDOM_ENGINE);
    Linear dense3(5, 3, A_RANDOM_ENGINE);
//    ReLU activ1;
    TanH activ1;
    Sigmoid activ2;
    SoftMax activ3;
    SGD optim(0.01);
    CrossEntropy loss;
    vector<double> output;
    for(int epoch =0;epoch<1000;++epoch){
        int right = 0;
        for(int i =0;i<p.first.size(); ++i){
            output = dense1.forward(p.first[i]);
            output = activ1.forward(output);
            output = dense2.forward(output);
            output = activ2.forward(output);
            output = dense3.forward(output);
            output = activ3.forward(output);
//            cout <<"forward end" << endl;
            double max_p = -1;
            int x_pred = 0;
            for(int i =0;i <3;++i){
                if(max_p < output[i]){
                    max_p = output[i];
                    x_pred = i;
                }
            }
            if(x_pred == p.second[i]){
                ++right;
            }
//            cout << "loss:" << loss.forward(output, p.second[i]) << endl;
            loss.forward(output, p.second[i]);
            vector<double> g = loss.backward();
            g = activ3.backward(g, &optim);
            g = dense3.backward(g, &optim);
            g = activ2.backward(g, &optim);
            g = dense2.backward(g, &optim);
            g = activ1.backward(g, &optim);
            g = dense1.backward(g, &optim);
//            cout <<"backward end";
            dense1.zero_grad();
            dense2.zero_grad();
            dense3.zero_grad();
            activ1.zero_grad();
            activ2.zero_grad();
            activ3.zero_grad();
        }
        double precent = double(right) / double(p.first.size());
        cout << "Epoch " << epoch << ":" << precent << "," << right << endl;
    }
}

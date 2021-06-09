//
// Created by baiyun on 2021/6/9.
//
#include "module.h"
#include <iostream>
#include <cmath>
using namespace std;
Linear::Linear(int input_num, int output_num,  default_random_engine& e) {
    this -> input_num = input_num;
    this->output_num = output_num;
    for(int i =0;i < output_num;++i){
        Neuron a(input_num, e);
        this->nodes.push_back(a);
        a.output_weight();
    }
//    cout << this->nodes.size() << endl;
}
vector<double> Linear::forward(vector<double> X){
//    for(auto c:X){
//        cout << c << endl;
//    }
    vector<double> ret;
//    this->input = X;
    for(int i =0;i<output_num;++i){
        double node_ans = this->nodes[i].forward(X);
//        cout << node_ans << "fck";
        ret.push_back(node_ans);
    }
    return ret;
}

vector<double> Linear::backward(vector<double> gradients, optim* opt){
    vector<double> ret;
    for(int i =0; i<this->input_num;++i){
        ret.push_back(0);
    }
    for(int i = 0;i< this->nodes.size();++i){
        this->nodes[i].update(gradients[i], opt);
        vector<double> neuron_weights = this->nodes[i].backward(gradients[i]);
        for(int j =0;j<this->input_num;++j){
            ret[j] += neuron_weights[j];
        }
    }
    return ret;
}
void Linear::zero_grad() {
    for(int i =0;i<nodes.size();++i){
        nodes[i].zero_grad();
    }
}

vector<double> ReLU::forward(std::vector<double> X) {
    this->input = X;
    for(int i = 0;i<X.size();++i){
        if(X[i] < 0){
            X[i] = 0;
        }
    }
    return X;
}
vector<double> ReLU::backward(std::vector<double> gradient, optim *opt) {
    vector<double> ret;
    for(int i =0;i<gradient.size();++i){
        if(this->input[i] > 0){ret.push_back(gradient[i]);}
        else{ret.push_back(0);}
    }
    return ret;
}

std::vector<double> TanH::forward(std::vector<double> X){
    this->input= X;
    vector<double>ret;
    for(int i =0;i <X.size();++i){
        ret.push_back(forwardcal(X[i]));
    }
    return ret;
}
double TanH::backwardcal(double input) {
    return  1 - pow(this->forwardcal(input), 2);
}
double TanH::forwardcal(double input) {
    double ret;
    double a =exp(input);
    double b = exp(-1.0*input);
    ret = (a - b) / (a+b);
    return ret;
}
std::vector<double> TanH::backward(std::vector<double> gradient, optim * opt){
    vector<double> ret;
    for(int i =0;i<this->input.size();++i){
        ret.push_back(gradient[i] * this->backwardcal(this->input[i]));
    }
    return ret;
}


std::vector<double> Sigmoid::forward(std::vector<double> X){
    this->input= X;
    vector<double>ret;
    for(int i =0;i <X.size();++i){
        ret.push_back(forwardcal(X[i]));
    }
    return ret;
}
double Sigmoid::backwardcal(double input) {
    double minus_exp = exp(-1.0 * input);
    double t = 1.0/(1.0 + minus_exp);
    return t* (1-t);
}
double Sigmoid::forwardcal(double input) {
    return 1.0/(1.0 + exp(-1.0*input));
}
std::vector<double> Sigmoid::backward(std::vector<double> gradient, optim * opt){
    vector<double> ret;
    for(int i =0;i<this->input.size();++i){
        ret.push_back(gradient[i] * this->backwardcal(this->input[i]));
    }
    return ret;
}
double CrossEntropy::forward(vector<double> x, int y){
    this->x = x;
    vector<double> y_mat;
//    cout <<"loss input:" << endl;
    for(int i =0;i < x.size();++i){
        y_mat.push_back(0);
//        cout << x[i] << " ";
    }
//    cout << endl;
    y_mat[y]= double(1);
    this->y = y_mat;
    double ret = 0;
    for(int i =0;i < x.size() ;++i) {
        ret += (y_mat[i] * log(x[i]));
    }
    return -1.0 * ret;
}
std::vector<double>CrossEntropy::backward(){
    vector<double> ret;
    for(int i =0;i < this->x.size();++i){
        ret.push_back(this->x[i] - this->y[i]);
    }
    return ret;
}
//std::vector<double>CrossEntropy::backward(){
//    vector<double> ret;
//    for(int i =0;i<this->x.size();++i){
//        if(this->y[i] == 0){
//            ret.push_back(0);
//        }else{
//            ret.push_back(1.0/this->x[i]);
//        }
//    }
//    return ret;
//}
std::vector<double> SoftMax::forward(std::vector<double> X) {
    this->x = X;
    vector<double> ret;
    double smm = 0;
    for(auto c: X){
        double expc = exp(c);
        smm += expc;
        ret.push_back(expc);
    }
    for(int i =0;i<ret.size();++i){
        ret[i] = ret[i] /smm;
    }
    return ret;

}
std::vector<double> SoftMax::backward(vector<double>pre_gradient, optim *opt) {
    vector<double> X_exp;
    double smm = 0;
    for(int i =0;i<this->x.size();++i){
        X_exp.push_back(exp(this->x[i]));
        smm += X_exp.back();
    }
    vector<double>ret;
    for(int i =0;i<this->x.size();++i){
        ret.push_back(pre_gradient[i]*X_exp[i]*(smm-1)/pow(smm,2));
    }
    return ret;
}

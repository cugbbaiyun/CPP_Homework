#include <iostream>
#include <vector>
#include "data_utils.h"
#include "consts.h"
using namespace  std;
int main() {
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
}

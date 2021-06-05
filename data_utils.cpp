//
// Created by baiyun on 2021/6/5.
//

#include "data_utils.h"
#include <fstream>
#include <climits>
#include <cctype>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool MyData::read(std::string line){
    bool is_empty=1;
    for(auto & c: line){
        if(c == ','){c = ' ';}
        if(!isspace(c)){is_empty=0;}
    }
    if(is_empty)return 0;
    std::stringstream line_in(line);
    double t;
    for(int i =0;i<4;++i){
        line_in >> t;
        this->x.push_back(t);
    }
    line_in >> this->y;
    return 1;
}
std::vector<MyData> read_data(std::string FileName){
    std::vector<MyData> ret;
    std::string line;
    std::fstream in(FileName);
    while(getline(in, line)){
        MyData d;
        bool read_success = d.read(line);
        if(read_success){
            ret.push_back(d);
        }
    }
    return ret;
}

map<string, int> read_names(vector<MyData> datas){
    map<string, int> mm;
    for(auto c:datas){
        if(mm.find(c.y) == mm.end()){
            mm[c.y] = mm.size();
        }
    }
    return mm;
}
int name2class(string name, map<string,int> names){
    if(names.find(name) == names.end()){return -1;}
    return names[name];
}
pair<vector<vector<double>>, vector<int>> getdataxy(vector<MyData> datas, map<string,int>names, bool random){
    if(random){
        srand(time(NULL));
        for(auto& c:datas) {
            c.rand_num = rand();
        }
        sort(datas.begin(), datas.end(),[&](MyData a, MyData b){return a.rand_num < b.rand_num;});
    }
    vector<vector<double>> x;
    vector<int> y;
    for(auto c:datas){
        x.push_back(c.x);
        y.push_back(name2class(c.y, names));
    }
    return pair<vector<vector<double>>, vector<int>>(x, y);
}

void normalize(vector<vector<double>>& x){
    for(int i =0;i<x[0].size();++i) {
        double min_x = INT_MAX;
        double max_x = INT_MIN;
        for (auto c: x) {
            if (c[i] > max_x) { max_x = c[i]; }
            if (c[i] < min_x) { min_x = c[i]; }
        }
        for (auto &c:x) {
            c[i] = (c[i] - min_x) / (max_x - min_x);
        }
    }
}
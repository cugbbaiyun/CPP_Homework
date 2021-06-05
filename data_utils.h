//
// Created by baiyun on 2021/6/5.
//

#ifndef IRIS_DATA_UTILS_H
#define IRIS_DATA_UTILS_H

#endif //IRIS_DATA_UTILS_H
#include <vector>
#include <string>
#include <map>
#include <iostream>

struct MyData{
    std::vector<double> x;
    std::string y;
    bool read(std::string line);
    MyData()=default;
    ~MyData()=default;
    void output(){
        std::cout << "x:";
        for(auto c:x){
            std::cout << c << ",";
        }
        std::cout << std::endl << "y:"<<this->y << std::endl;
    }
    int rand_num;
};
std::vector<MyData> read_data(std::string FileName);
std::map<std::string, int> read_names(std::vector<MyData> datas);
int name2class(std::string name, std::map<std::string, int> names);
std::pair<std::vector<std::vector<double>>, std::vector<int>> getdataxy(std::vector<MyData> datas, std::map<std::string, int> names,bool random=1);
void normalize(std::vector<std::vector<double>>& x);
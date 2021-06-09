//
// Created by baiyun on 2021/6/5.
//

#ifndef IRIS_NEURON_H
#define IRIS_NEURON_H

#include<iostream>
#include <vector>
#include "optim.h"
#include"consts.h"
struct Neuron{
private:
//    std::vector<std::vector<double>> input;
    std::vector<double> input;
    int input_num = input_num;
    int bias = 0;
    std::vector<double>weight;
    double pre_gradient;
    std::vector<double> pre_weight;
    double old_gradient = 0;
//    std::vector<double> pre_bias;
    double pre_bias = 0;
public:
    Neuron(int input_num, std::default_random_engine& e){
        this->init(input_num, e);
    }
    void init(int input_num, std::default_random_engine& e);
    void zero_grad();
    void update(double gradient, optim* opt);
    std::vector<double> backward(double gradient);
    double forward(std::vector<double> X);
    void output_weight(){
        std::cout <<"Neuron:";
        for(auto c:weight){
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
};

#endif //IRIS_NEURON_H

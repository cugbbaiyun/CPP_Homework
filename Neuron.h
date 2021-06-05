//
// Created by baiyun on 2021/6/5.
//

#ifndef IRIS_NEURON_H
#define IRIS_NEURON_H

#endif //IRIS_NEURON_H
#include <vector>
#include "optim.h"
struct Neuron{
private:
    std::vector<std::vector<double>> input;
    int input_num = input_num;
    int bias = 0;
    std::vector<double>weight;
    double pre_gradient;
    std::vector<double> pre_weight;
//    std::vector<double> pre_bias;
    double pre_bias = 0;
public:
    void init(int input_num);
    void zero_grad();
    void update(double pre_gradient, optim* opt);
    std::vector<double> backward(double pre_gradient);
    double forward(std::vector<double> X);
};
//
// Created by baiyun on 2021/6/5.
//
#include "Neuron.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <random>
using namespace std;

void Neuron::init(int input_num, default_random_engine& A_RANDOM_ENGINE){
    this->input_num = input_num;
    std::normal_distribution<double> dis(0,1);
    for(int i =0;i<input_num;++i){
        this->weight.push_back(dis(A_RANDOM_ENGINE));
    }
    this->bias = 0;
    this->pre_gradient = 0;
    this->old_gradient = 0;
}
void Neuron::zero_grad(){
    this->input.clear();
    this->old_gradient = 0;
}
void Neuron::update(double gradient, optim* opt){
    this->old_gradient = this->pre_gradient;
    this->pre_gradient = gradient;
    this->pre_weight = this->weight;
    this->pre_bias = this->bias;
    for(int i =0;i<this->weight.size();++i){
        this->weight[i] = opt->update(this->weight[i], this->pre_gradient*this->input[i], this->old_gradient);
    }
    this->bias = opt->update(this->bias, this->pre_gradient, this->old_gradient);
}
vector<double> Neuron::backward(double gradient) {
    vector<double> ret;
    for(auto c: this->weight){
        ret.push_back(gradient * c);
    }
    return ret;
}
double Neuron::forward(vector<double> X) {
    double ret = 0;
    this->input = X;
    for(int i =0;i<X.size();++i){
        ret += (this->weight[i] * X[i]);
    }
    ret += this->bias;
    return ret;
}
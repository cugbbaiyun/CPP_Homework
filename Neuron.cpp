//
// Created by baiyun on 2021/6/5.
//
#include "Neuron.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "optim.h"
using namespace std;

void Neuron::init(int input_num){
    srand(time(NULL));
    this->input_num = input_num;
    for(int i =0;i<input_num;++i){
        this->weight.push_back(double(rand()%1000+1)/1000.0);
        this->pre_weight.push_back(0);
    }
    this->bias = 0;
    this->pre_gradient = 0;
}
void Neuron::zero_grad(){
    this->input.clear();
}
void Neuron::update(double pre_gradient, optim* opt){
    this->pre_gradient = pre_gradient;
    this->pre_weight = this->weight;
    this->pre_bias = this->bias;
    this->bias = opt->update(this->bias, this->pre_gradient);
    for(int i =0;i<this->weight.size();++i){

    }
}
std::vector<double> backward(double pre_gradient);
double forward(vector<double> X);
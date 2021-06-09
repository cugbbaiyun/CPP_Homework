//
// Created by baiyun on 2021/6/9.
//
#include <vector>
#include "Neuron.h"
#include "optim.h"
#include <random>

#ifndef IRIS_MODULE_H
#define IRIS_MODULE_H

struct Module{
    Module() =default;
    virtual std::vector<double> forward(std::vector<double> X){
        std::vector<double> ret;
        return ret;
    }
    virtual std::vector<double> backward(std::vector<double> gradient, optim* opt){
        std::vector<double> ret;
        return ret;
    }
    virtual void zero_grad(){
        return;
    }
};

struct Linear:public Module{
private:
    std::vector<Neuron> nodes;
    int input_num;
    int output_num;
public:
    Linear(int input_num, int output_num, std::default_random_engine& e);
    std::vector<double> forward(std::vector<double> X);
    std::vector<double> backward(std::vector<double> gradient, optim * opt);
    void zero_grad();
};

struct ReLU: public Module{
private:
    std::vector<double> input;
public:
    ReLU() = default;
    std::vector<double> forward(std::vector<double> X);
    std::vector<double> backward(std::vector<double> gradient, optim * opt);
    void zero_grad(){
        input.clear();
    }
};

struct TanH:public Module{
private:
    std::vector<double> input;
    double forwardcal(double input);
    double backwardcal(double input);
public:
    TanH() = default;
    std::vector<double> forward(std::vector<double> X);
    std::vector<double> backward(std::vector<double> gradient, optim * opt);
    void zero_grad(){
        input.clear();
    }
};

struct Sigmoid:public Module{
private:
    std::vector<double> input;
    double forwardcal(double input);
    double backwardcal(double input);
public:
    Sigmoid() = default;
    std::vector<double> forward(std::vector<double> X);
    std::vector<double> backward(std::vector<double> gradient, optim * opt);
    void zero_grad(){
        input.clear();
    }
};
struct CrossEntropy{
private:
    std::vector<double> x;
    std::vector<double> y;
public:
    double forward(std::vector<double>X, int Y);
    std::vector<double>backward();
};
struct SoftMax:public Module{
private:
    std::vector<double> x;
public:
    std::vector<double> forward(std::vector<double>X);
    std::vector<double> backward(std::vector<double> pregraident, optim* opt);
    void zero_grad(){this->x.clear();}
};
#endif //IRIS_MODULE_H

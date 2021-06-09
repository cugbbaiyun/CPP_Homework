//
// Created by baiyun on 2021/6/5.
//

#ifndef IRIS_OPTIM_H
#define IRIS_OPTIM_H

#include <iostream>
struct optim{
public:
    double lr = 0.01;
    optim(double learning_rate):lr(learning_rate){}
    virtual double update(double data, double gradient, double pre_gradient){
        return data - this->lr*gradient;
    }
};
struct SGD:public optim{
public:
    SGD(double lr): optim(lr){}
    double update(double data, double gradient=0, double pre_gradient=0){
        return data - this->lr*gradient;
    }
};
struct DoubleSGD:public optim{
public:
    DoubleSGD(double lr): optim(lr){}
    double update(double data,double gradient=0, double pre_gradient=0){
        double grad = 0;
        if(pre_gradient == 0){
            grad = gradient;
        }else if(pre_gradient * gradient > 0){
            grad = 2 *gradient;
        }else{
            grad = gradient/2;
        }
        double ret = data - this->lr * grad;
        return ret;
    }
};
struct Momentum:public optim{
public:
    Momentum(double lr, double gamma=0.9):optim(lr), gm(gamma){}
    double update(double data, double gradient, double& pre_gradient){
        pre_gradient = this->gm * pre_gradient + this->lr * gradient;
        double ret = data - pre_gradient;
        return ret;
    }
private:
    double gm = 0.9;
};
#endif //IRIS_OPTIM_H

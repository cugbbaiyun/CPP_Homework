//
// Created by baiyun on 2021/6/5.
//
struct optim{
private:
    double lr = 0.01;
public:
    void init(double learning_rate):lr(learning_rate){}

}
struct SGD{
public:
    double lr = 0.01;
    double update(double data, double gradient){
        return data - this->lr * gradient;
    }
};
//
// Created by sara on 17/12/18.
//

#ifndef MILESTONE1_EXPRESSION_H
#define MILESTONE1_EXPRESSION_H

#include <iostream>
using namespace std;
class Expression {
public:
    virtual double calculate() = 0;
    virtual ~Expression()=default;
};


#endif //MILESTONE1_EXPRESSION_H

//
// Created by sara on 17/12/18.
//

#ifndef MILESTONE1_NUMBER_H
#define MILESTONE1_NUMBER_H


#include "Expression.h"

class Number : public Expression {
    double m_val;
public:
    Number(double val);
    virtual double calculate();
    virtual ~Number()=default;
};


#endif //MILESTONE1_NUMBER_H

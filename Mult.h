//
// Created by sara on 17/12/18.
//

#ifndef MILESTONE1_MULT_H
#define MILESTONE1_MULT_H


#include "BinaryExpression.h"

class Mult : public BinaryExpression{
public:
    Mult(Expression* left, Expression* right);
    Mult();
    virtual double calculate();
    virtual void setRight(Expression* right);
    virtual void setLeft(Expression* left);
};


#endif //MILESTONE1_MULT_H

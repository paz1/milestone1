//
// Created by sara on 17/12/18.
//

#ifndef MILESTONE1_MINUS_H
#define MILESTONE1_MINUS_H


#include "BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus(Expression* left, Expression* right);
    Minus();
    virtual double calculate();
    virtual void setRight(Expression* right);
    virtual void setLeft(Expression* left);
};


#endif //MILESTONE1_MINUS_H

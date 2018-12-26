//
// Created by sara on 18/12/18.
//

#ifndef MILESTONE1_DIV_H
#define MILESTONE1_DIV_H


#include "BinaryExpression.h"
class Div : public BinaryExpression{
public:
    Div(Expression* left, Expression* right);
    Div();
    virtual double calculate();
    virtual void setRight(Expression* right);
    virtual void setLeft(Expression* left);
    //virtual ~Div()=default;
};


#endif //MILESTONE1_DIV_H

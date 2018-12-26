//
// Created by sara on 17/12/18.
//

#ifndef MILESTONE1_PLUS_H
#define MILESTONE1_PLUS_H

#include "BinaryExpression.h"

class Plus : public BinaryExpression{
public:
    Plus(Expression* left, Expression* right);
    Plus();
    virtual double calculate();
    virtual void setRight(Expression* right);
    virtual void setLeft(Expression* left);
};


#endif //MILESTONE1_PLUS_H

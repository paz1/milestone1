//
// Created by sara on 17/12/18.
//

#include "Plus.h"

Plus::Plus(Expression* left, Expression* right) : BinaryExpression(left, right){};
Plus::Plus(): BinaryExpression(new Number(0), new Number(0)) {}
double Plus::calculate() {
    return m_left->calculate() + m_right->calculate();
}
void Plus::setRight(Expression* right){
    BinaryExpression::setRight(right);
}
void Plus::setLeft(Expression* left){
    BinaryExpression::setLeft(left);
}
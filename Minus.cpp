//
// Created by sara on 17/12/18.
//

#include "Minus.h"

Minus::Minus(Expression* left, Expression* right): BinaryExpression(left, right) {};
Minus::Minus(): BinaryExpression(new Number(0), new Number(0)) {}
double Minus::calculate() {
    return m_left->calculate() - m_right->calculate();
}
void Minus::setRight(Expression* right){
    BinaryExpression::setRight(right);
}
void Minus::setLeft(Expression* left){
    BinaryExpression::setLeft(left);
}
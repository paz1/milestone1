//
// Created by sara on 17/12/18.
//

#include "Mult.h"

Mult::Mult(Expression* left, Expression* right): BinaryExpression(left, right) {};
Mult::Mult(): BinaryExpression(new Number(0), new Number(0)) {}
double Mult::calculate() {
    return m_left->calculate() * m_right->calculate();
}
void Mult::setRight(Expression* right){
    BinaryExpression::setRight(right);
}
void Mult::setLeft(Expression* left){
    BinaryExpression::setLeft(left);
}
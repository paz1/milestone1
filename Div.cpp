//
// Created by sara on 18/12/18.
//

#include "Div.h"

Div::Div(Expression* left, Expression* right): BinaryExpression(left, right) {};
Div::Div(): BinaryExpression(new Number(0), new Number(1)) {}
double Div::calculate() {
    if(m_right->calculate() == 0){
        delete m_right;
        delete m_left;
         throw "Can't Divide by zero";
    }
    return m_left->calculate() / m_right->calculate();
}
void Div::setRight(Expression* right){
    BinaryExpression::setRight(right);
}
void Div::setLeft(Expression* left){
    BinaryExpression::setLeft(left);
}


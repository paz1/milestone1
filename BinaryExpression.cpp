//
// Created by sara on 17/12/18.
//

#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression* left, Expression* right) {
    this->m_left = left;
    this->m_right = right;
}
void BinaryExpression::setRight(Expression* right){
    delete(this->m_right);
    this->m_right = right;
}
void BinaryExpression::setLeft(Expression* left){
    delete this->m_left;
    this->m_left = left;
}
BinaryExpression::~BinaryExpression(){
    delete (this->m_left);
    delete (this->m_right);
}

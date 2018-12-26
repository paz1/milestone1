//
// Created by sara on 17/12/18.
//

#ifndef MILESTONE1_BINARYEXPRESSION_H
#define MILESTONE1_BINARYEXPRESSION_H

#include "Expression.h"
#include "Number.h"

class BinaryExpression : public Expression {
protected:
    Expression* m_left;
    Expression* m_right;
public:
    BinaryExpression(Expression* left, Expression* right);
    virtual void setRight(Expression* right);
    virtual void setLeft(Expression* left);
    virtual ~BinaryExpression();

};
#endif //MILESTONE1_BINARYEXPRESSION_H

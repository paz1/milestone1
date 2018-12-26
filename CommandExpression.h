//
// Created by paz on 17/12/18.
//

#ifndef MILESTONE1_COMMANDEXPRESSION_H
#define MILESTONE1_COMMANDEXPRESSION_H


#include "Expression.h"
#include "Command.h"

class CommandExpression: public Expression {
    Command* c;
    vector<string> vec;
    SymbolTable* st;
public:
    CommandExpression(Command* c,SymbolTable* st,vector<string>vec);
    virtual double calculate();
    ~CommandExpression();
};


#endif //MILESTONE1_COMMANDEXPRESSION_H

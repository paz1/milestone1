//
// Created by paz on 18/12/18.
//

#ifndef MILESTONE1_CONDITIONPARSER_H
#define MILESTONE1_CONDITIONPARSER_H


#include "Command.h"
#include "Expression.h"

class ConditionParser: public Command {
protected:
    vector<Expression*> commands;
    bool flag;
public:
    void doCommand(vector<string> vec, SymbolTable *st);
    ConditionParser(vector<Expression*> commands);
    ~ConditionParser();
};


#endif //MILESTONE1_CONDITIONPARSER_H

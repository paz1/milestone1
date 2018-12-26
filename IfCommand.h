//
// Created by paz on 17/12/18.
//

#ifndef MILESTONE1_IFCOMMAND_H
#define MILESTONE1_IFCOMMAND_H


#include "ConditionParser.h"

class IfCommand : public ConditionParser {
public:
    virtual void doCommand(vector<string> vec,SymbolTable* st);
    IfCommand(vector<Expression*>commands);
};


#endif //MILESTONE1_IFCOMMAND_H

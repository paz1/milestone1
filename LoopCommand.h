//
// Created by paz on 16/12/18.
//

#ifndef MILESTONE1_LOOPCOMMAND_H
#define MILESTONE1_LOOPCOMMAND_H


#include "ConditionParser.h"

class LoopCommand : public ConditionParser {
public:
    virtual void doCommand(vector<string> vec,SymbolTable* st);
    LoopCommand(vector<Expression*>commands);

};


#endif //MILESTONE1_LOOPCOMMAND_H

//
// Created by paz on 16/12/18.
//

#ifndef MILESTONE1_PRINTCOMMAND_H
#define MILESTONE1_PRINTCOMMAND_H


#include "Command.h"

class PrintCommand  : public Command {
public:
    virtual void doCommand(vector<string> vec,SymbolTable* st);
    void checkIsValid(vector<string> vec,SymbolTable* st);
};


#endif //MILESTONE1_PRINTCOMMAND_H

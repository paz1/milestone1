//
// Created by paz on 18/12/18.
//

#ifndef MILESTONE1_DEFINEVARCOMMAND_H
#define MILESTONE1_DEFINEVARCOMMAND_H


#include "Command.h"

using namespace std;
class DefineVarCommand: public Command {

public:
    virtual void doCommand(vector<string> vec,SymbolTable *st);
    void checkIsValid(vector<string> vec);
};


#endif //MILESTONE1_DEFINEVARCOMMAND_H

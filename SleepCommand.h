//
// Created by paz on 18/12/18.
//

#ifndef MILESTONE1_SLEEPCOMMAND_H
#define MILESTONE1_SLEEPCOMMAND_H

#include "Command.h"

using namespace std;
class SleepCommand: public Command {
    virtual void doCommand(vector<string> vec,SymbolTable* st);
    void checkIsValid(vector<string> vec,SymbolTable* st);
};


#endif //MILESTONE1_SLEEPCOMMAND_H

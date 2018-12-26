//
// Created by paz on 16/12/18.
//

#ifndef MILESTONE1_COMMAND_H
#define MILESTONE1_COMMAND_H

#include <string>
#include <vector>
#include "SymbolTable.h"

using namespace std;

class Command  {

public:
    virtual void doCommand(vector<string> vec,SymbolTable *st)=0;
    virtual ~Command()= default;
};


#endif //MILESTONE1_COMMAND_H

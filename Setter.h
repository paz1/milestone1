//
// Created by paz on 18/12/18.
//

#ifndef MILESTONE1_SETTER_H
#define MILESTONE1_SETTER_H


#include "Command.h"

class Setter : public Command {
    void doCommand(vector<string> vec,SymbolTable* st);
    void checkIsValid(vector<string> vec,SymbolTable* st);
};


#endif //MILESTONE1_SETTER_H

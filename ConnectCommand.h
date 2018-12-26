//
// Created by paz on 16/12/18.
//

#ifndef MILESTONE1_CONNECTCOMMAND_H
#define MILESTONE1_CONNECTCOMMAND_H


#include "Command.h"

class ConnectCommand : public Command {
public:
    virtual void doCommand(vector<string> vec,SymbolTable* st);
    void checkIsValid(vector<string> vec);
    void connecting(vector<string> vec,SymbolTable* st);
};


#endif //MILESTONE1_CONNECTCOMMAND_H

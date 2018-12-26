//
// Created by paz on 16/12/18.
//

#ifndef MILESTONE1_OPENSERVERCOMMAND_H
#define MILESTONE1_OPENSERVERCOMMAND_H


#include "Command.h"

class OpenServerCommand : public Command {
public:
virtual void doCommand(vector<string> vec,SymbolTable* st);
void checkIsValid(vector<string> vec);
int openNewServer(vector<string> vec,SymbolTable* st);
void readData(int fd,SymbolTable* st);
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H

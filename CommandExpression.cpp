//
// Created by paz on 17/12/18.
//

#include "CommandExpression.h"
double CommandExpression::calculate(){
    c->doCommand(this->vec,st);
    return 0;
}
CommandExpression::CommandExpression(Command* c,SymbolTable* st,vector<string> vec){
    this->c=c;
    this->st=st;
    this->vec=vec;
}
CommandExpression::~CommandExpression(){
    delete(c);
}
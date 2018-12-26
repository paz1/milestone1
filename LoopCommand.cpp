//
// Created by paz on 16/12/18.
//

#include "LoopCommand.h"
void LoopCommand::doCommand(vector<string> vec,SymbolTable* st){
    ConditionParser::doCommand(vec,st);
    while(this->flag) {
        for (int i = 0; i < this->commands.size(); i++) {
            commands.at(i)->calculate();
        }
        ConditionParser::doCommand(vec, st);
    }
    //this->flag=true;


}
LoopCommand::LoopCommand(vector<Expression*>commands):ConditionParser(commands){}

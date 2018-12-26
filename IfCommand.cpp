//
// Created by paz on 17/12/18.
//

#include "IfCommand.h"
void IfCommand::doCommand(vector<string> vec,SymbolTable* st){
    ConditionParser::doCommand(vec,st);
    if(this->flag) {
        for (int i = 0; i < this->commands.size(); i++) {
            commands.at(i)->calculate();
        }
    }
}
IfCommand::IfCommand(vector<Expression*>commands):ConditionParser(commands){}

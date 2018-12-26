//
// Created by paz on 16/12/18.
//

#include <iostream>
#include "PrintCommand.h"
#include "ExpressionCreator.h"

void PrintCommand::doCommand(vector<string> vec,SymbolTable* st) {
    checkIsValid(vec,st);
    //todo print expression or exp with vars

    if(vec.at(1).at(0)!='"'){
/*        //expression
        if(!st->hasVarValue(vec.at(1))){
            cout<<vec.at(1);
        }
        //print var
        else*/
        Expression* exp=ExpressionCreator::createExpression(vec.at(1),st);
        cout <<exp->calculate()<<endl;
        delete(exp);
        return;
    }
    //print "..."
    cout<<vec.at(1).substr(1,vec.at(1).length()-2)<<endl;

}
void PrintCommand::checkIsValid(vector<string> vec,SymbolTable* st){
    /*if(vec.at(1).at(0)!='"'){
        //if it not in the map
        if(!(st->hasVarValue(vec.at(1)))) {
            __throw_invalid_argument("invalid argument");
        }
    }*/
}

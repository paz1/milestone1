//
// Created by paz on 18/12/18.
//

#include <chrono>
#include <thread>
#include <map>
#include <algorithm>

#include "SleepCommand.h"
#include "ExpressionCreator.h"

void SleepCommand::doCommand(vector<string> vec,SymbolTable* st){
    checkIsValid(vec,st);
    double sec;
    //from the map
    if(st->hasVarValue(vec.at(1))){
        sec= st->getVarValue(vec.at(1));
    }
    //expression
    else{
        Expression* exp=ExpressionCreator::createExpression(vec.at(1),st);
        sec=exp->calculate();
        delete(exp);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds((long)sec));

}
void SleepCommand::checkIsValid(vector<string> vec,SymbolTable* st){
    if(vec.size()!=2){
        __throw_invalid_argument("no match parameters");
    }
    //if it not in the map
    if(!(st->hasVarValue(vec.at(1)))) {
        //check if it number
        stoi(vec.at(1));
    }
}
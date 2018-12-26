//
// Created by paz on 18/12/18.
//

#include <algorithm>
#include "DefineVarCommand.h"
#include "ExpressionCreator.h"

void DefineVarCommand::doCommand(vector<string> vec,SymbolTable* st){
    checkIsValid(vec);
    string s;
    bool needToBind=false;
    // var x = bind y
    if(vec.size()==5) {
        s=vec.at(4);
        needToBind=true;
    }
    // var x = y
    else if(vec.size()==4){
        s=vec.at(3);
    }
    // path "/.../..."
    if(s.at(0)=='"'){
        string p;
        p=s.substr(1,s.length()-2);
        if(needToBind){
            st->setBind(vec.at(1),p);
        }
        if(!st->hasPath(p)){
            st->setPathValue(p);
        }
        st->setVarValue(vec.at(1),st->getPathValue(p));
    }
    //add to the symbol table if it exist var
    else if(st->hasVarValue(s)){
        if(needToBind){
            st->setBind(vec.at(1),st->getBindPath(s));
        }
        st->setVarValue(vec.at(1), st->getVarValue(s));
    }
    // if it number
    else{
        Expression* exp=ExpressionCreator::createExpression(s,st);
         double num =exp->calculate();
         delete(exp);
        st->setVarValue(vec.at(1), num);

    }
}
void DefineVarCommand::checkIsValid(vector<string> vec){
    if(vec.size()==5){
        if(vec.at(3)!="bind")
            __throw_invalid_argument("invalid var");
    }
    else if(vec.size()!=4){
        __throw_invalid_argument("no match paremeters");
    }
    if(vec.at(2)!="=")
        __throw_invalid_argument("invalid var");
    vector<string> saveNames={"var","connect","openDataServer","while","if","print","sleep"};
    if(find(saveNames.begin(), saveNames.end(), vec.at(1)) != saveNames.end())
        __throw_invalid_argument("using in save name");
    int i=0;
    while(i<vec.at(1).size()){
        char c=vec.at(1).at(i);
        if(i==0&&(c>='0'&&c<='9'))
            __throw_invalid_argument("invalid var name");
        if(((!(c>='a'&&c<='z'))&&(!(c>='A'&&c<='Z')))&&((!(c>='0'&&c<='9'))&&(c!='_')))
            __throw_invalid_argument("invalid var name");
        i++;

    }
    if((vec.at(1).at(0)=='"'&&vec.at(1).at(vec.at(1).size()-1)!='"')||
        vec.at(1).at(0)!='"'&&vec.at(1).at(vec.at(1).size()-1)=='"')
    {
        __throw_invalid_argument("invalid path");
    }
}
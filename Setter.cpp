//
// Created by paz on 18/12/18.
//

#include <sys/socket.h>
#include <unistd.h>
#include "Setter.h"
#include "ExpressionCreator.h"
#include "ConnectCommand.h"
extern int cnctfd;
void Setter::doCommand(vector<string> vec,SymbolTable* st){
    checkIsValid(vec,st);
    double d;
    //in the map
    if(st->hasVarValue(vec.at(2))){
        d= st->getVarValue(vec.at(2));
    }
    // expression
    else {
        Expression* exp=ExpressionCreator::createExpression(vec.at(2),st);
        d = exp->calculate();
        delete(exp);
    }
    st->setVarValue(vec.at(0), d);
    //update all the connected binds
    if(st->hasBindPath(vec.at(0))){
        string s=st->getBindPath(vec.at(0));
        //st->setPathValue(s,d);
        //st->updateBinds(s,d);
        //send info
        string message;
        message=  "set " +s+ " " + to_string(d)+"\r\n";
        /* Send message to the server */
        int n = write(cnctfd, message.c_str(), strlen(message.c_str()));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }

}
void Setter::checkIsValid(vector<string> vec,SymbolTable* st){
/*    if(vec.size()==3){
        if(vec.at(1)!="=")
            __throw_invalid_argument("no match params");
        //if it not in the map
*//*        if(!(st->hasVarValue(vec.at(2)))) {
            //check if it number
            stoi(vec.at(2));
        }*//*
    }
    else{
        __throw_invalid_argument("no match params");
    }*/

}

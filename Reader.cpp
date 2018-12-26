//
// Created by paz on 17/12/18.
//

#include <sstream>
#include <fstream>
#include "Reader.h"
#include "OpenServerCommand.h"
#include "CommandExpression.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "Number.h"
#include "Setter.h"
#include "SleepCommand.h"
#include "ConditionParser.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "ExpressionCreator.h"
#include <algorithm>
#include <deque>
#include <unistd.h>

extern int cnctfd;
extern int ifConectServ;
extern int servfd;
void Reader::cutSpaces(string* s){
    string exp, temp;
    istringstream line(*s);
    while(getline(line,temp,' ')){
        exp+=temp;
    }
    *s = exp;
}
vector<string> Reader::separateExpressions(string line){
    vector<string> expressions;
    string exp;
    char prev = 0;
    bool operatorShow = false;
    bool flagForNum = false;
    for(char c:line){
        if(ExpressionCreator::isOperator(c)){
            exp+=c;
            operatorShow = true;
            flagForNum= false;
        } else if(ExpressionCreator::isLetter(c)||c == '_'||isdigit(c)!=0||c=='.'){
            // if there is space and no operator before it's space between expressions.
            if(!exp.empty() && !operatorShow && prev==' '){
                expressions.push_back(exp);
                exp.clear();
                if(flagForNum)
                    flagForNum=false;
            }
            if(isdigit(c)!=0||c=='.'){
                if(prev==' '||operatorShow)
                    flagForNum = true;
            } else {
                //if var started with number- throw exception
                if(flagForNum){
                    __throw_invalid_argument("Invalid var format");
                }
            }
            exp += c;
            operatorShow = false;
        } else if(c == ' '||c=='('||c==')'){
            if(c!=' '){
                exp+=c;
            }
        } else {
            break;
        }
        prev=c;
    }
    if(!exp.empty()){
        expressions.push_back(exp);
    }
    return expressions;
}
vector<string> Reader::connectLexer(string s, SymbolTable* st){
    vector<string> parsedLine;
    string connect = "connect";
    size_t isConnect = s.find(connect);
    parsedLine.push_back(connect);
    size_t startIP = isConnect+connect.length();
    s = s.substr(startIP);
    vector<string> vec = separateExpressions(s);
    if(vec.size()!=2){
        __throw_invalid_argument("Invalid arguments for connect command");
    }
    string legalFormat = "([0-9]+[.]){3}[0-9]+";
    regex legalIP(legalFormat);
    smatch IP;
    regex_match(vec[0], IP, legalIP);
    if(IP.empty()){
        __throw_invalid_argument("Invalid IP");
    }
    parsedLine.push_back(IP[0]);
    parsedLine.push_back(/*ExpressionCreator::convertToNumExp(*/vec[1]/*,st)[0]*/);
    return parsedLine;
}
vector<string> Reader::sleepLexer(string s, SymbolTable* st){
    vector<string> parsedLine;
    parsedLine.push_back("sleep");
    size_t startIndex= s.find(' ');
    if(startIndex!=0){
        __throw_invalid_argument("Must have space after sleep command");
    }
    vector<string> args = separateExpressions(s);
    if(args.size()!=1){
        __throw_invalid_argument("Invalid parameters for sleep command");
    }
    parsedLine.push_back(/*ExpressionCreator::convertToNumExp(*/args[0]/*,st)[0]*/);
    return parsedLine;
}
vector<string> Reader::printLexer(string s, SymbolTable* st) {
    vector<string> parsedLine;
    string print = "print";
    parsedLine.push_back(print);
    size_t startPath = s.find('"');
    if (startPath != string::npos) {
        size_t endPath = s.find('"', startPath + 1);
        string checkIfVaild = s.substr(endPath + 1);
        cutSpaces(&checkIfVaild);
        if (endPath == string::npos || checkIfVaild.length()) {
            __throw_invalid_argument("Invalid arguments for var command");
        }
        string msg = s.substr(startPath, endPath);
        parsedLine.push_back(msg);
    } else {
        // print expression
        size_t startIndex= s.find(print)+print.length();
        string msg = s.substr(startIndex);
        vector<string> vec = separateExpressions(msg);
        if(vec.size()!=1) {
            __throw_invalid_argument("Invalid arguments for print command");
        } else {
            parsedLine.push_back(/*ExpressionCreator::convertToNumExp(*/msg/*,st)[0]*/);
        }
    }
    return parsedLine;
}
vector<string> Reader::assignLexer(string s, SymbolTable* st){
    vector<string> parsedAssign;
    vector<string> split;
    istringstream line(s);
    string exp;
    vector<string> beforeAssignment = separateExpressions(s);
    for(string str: beforeAssignment){
        parsedAssign.push_back(str);
    }
    parsedAssign.push_back("=");
    vector<string> afterAssignment = separateExpressions(s.substr(s.find('=')+1));
    string checkIfValid;
    // bind with expression or bind to path
    if(afterAssignment[0] == "bind"){
        parsedAssign.push_back(afterAssignment[0]);
        // bind with path
        if(afterAssignment.size()==1) {
            size_t startPath = s.find('"')+1;
            if (startPath != string::npos) {
                size_t endPath = s.find('"', startPath );
                if (endPath == string::npos) {
                    __throw_invalid_argument("Invalid path to bind");
                }
                string path = s.substr(startPath-1, endPath - startPath+2);
                checkIfValid = s.substr(endPath + 1);
                cutSpaces(&checkIfValid);
                parsedAssign.push_back(path);
            }
        }else {
            // bind with var
            if (afterAssignment.size() != 2) {
                if (afterAssignment.size() == 3) {
                    checkIfValid = afterAssignment[2];
                    cutSpaces(&checkIfValid);
                } else {
                    __throw_invalid_argument("Invalid arguments for var command");
                }
            } else {
                //vector<string> vec = ExpressionCreator::convertToNumExp(afterAssignment[1], st);
                parsedAssign.push_back(afterAssignment[1]);
            }
        }
    } else {
        if(afterAssignment.size()!=1){
            if(afterAssignment.size()==2){
                checkIfValid = afterAssignment[1];
                cutSpaces(&checkIfValid);
            } else {
                __throw_invalid_argument("Invalid arguments for var command");
            }
        } else {
            //vector<string> vec = ExpressionCreator::convertToNumExp(afterAssignment[0],st);
            parsedAssign.push_back(afterAssignment[0]);
        }
    }
    if(!checkIfValid.empty()){
        if(checkIfValid != "}"){
            __throw_invalid_argument("Invalid arguments for var command");
        } else {
            parsedAssign.push_back(checkIfValid);
        }
    }
    return parsedAssign;
}
vector<string> Reader::openServerLexer(string s,SymbolTable* st){
    vector<string> parsedLine;
    string openData = "openDataServer";
    parsedLine.push_back(openData);
    s = s.substr(openData.length());
    vector<string> params = separateExpressions(s);
    if(params.size()!=2){
        __throw_invalid_argument("Number of arguments doesn't fit to command");
    } else {
        string firstParam = params[0];
        cutSpaces(&firstParam);
        /*vector<string> vec = *//*ExpressionCreator::convertToNumExp(*//*params[0]*//*,st*//*);
        for(string str:vec){
            firstParam += str;
        }
        vec.clear();*/
        string secondParam = params[1];
        cutSpaces(&secondParam);
        /*vec = *//*ExpressionCreator::convertToNumExp(*//*params[1]*//*,st*//*);
        for(string str:vec){
            secondParam += str;
        }*/
        parsedLine.push_back(firstParam);
        parsedLine.push_back(secondParam);
    }
    return parsedLine;
}
int Reader::isConditionalBlock(string s){
    size_t whileC = s.find("while");
    size_t ifC = s.find("if");
    if(whileC != string::npos){
        return 1;
    } else if(ifC != string::npos){
        return 2;
    } else {
        return 0;
    }
}
vector<string> Reader::lineLexer(string s){
    vector<string> parsedLine;
    size_t isAssign = s.find('=');
    size_t isPrint = s.find("print");
    size_t isSleep = s.find("sleep");
    size_t isOpenServer = s.find("openDataServer");
    size_t isConnect = s.find("connect");

    // case of bind or assign var
    if(isAssign != string::npos){
        return assignLexer(s, st);
    } else if(isPrint != string::npos){
        return printLexer(s, st);
    } else if(isSleep != string::npos){
        string sleep = "sleep";
        s = s.substr(isSleep+sleep.length());
        return sleepLexer(s,st);

    } else if(isConditionalBlock(s)){
        int condition = isConditionalBlock(s);
        size_t startIndex = 0;
        if(condition == 1){
            parsedLine.push_back("while");
            startIndex = s.find("while")+5;
        } else {
            parsedLine.push_back("if");
            startIndex = s.find("if")+2;
        }
        if(s.find('{')!=string::npos){
            size_t x=s.find('{');
            s = s.substr(startIndex,x-startIndex);
            cutSpaces(&s);
            parsedLine.push_back(s);
            parsedLine.push_back("{");
        } else {
            s = s.substr(startIndex);
            cutSpaces(&s);
            parsedLine.push_back(s);
        }
        return parsedLine;
    } else if(isOpenServer != string::npos){
        return openServerLexer(s,st);
    } else if(isConnect != string::npos) {
        return connectLexer(s,st);
    } else{
        cutSpaces(&s);
        if(s=="}"||s=="{"){
            parsedLine.push_back(s);
            return parsedLine;
        }
    }
}




void Reader::apply(string txt){
    fstream file;
    file.open (txt, fstream::in | fstream::out | fstream::app);
    ifstream infile(txt);
    if(file.peek() == ifstream::traits_type::eof()){
        return;
    }
    fillMap();
    string line;
    int brackets=0;
    vector<vector<string>> allLines;
    // lexer the lines
    while(getline(infile, line)) {
        if (line == "\n") {
            continue;
        }
        vector<string> lex = lineLexer(line);
        allLines.push_back(lex);
    }
    file.close();
    deque<Expression*> queue;
    int i=0;
    // parser the lines
    while(i<allLines.size()) {
        parserParams* par=parser(&allLines,i);
        if(par->exp!= nullptr)
        queue.push_back( par->exp);
        else{
            __throw_invalid_argument("too much brackets");
        }
        i=i+(par->i);
        delete(par);
    }
    //run all the commands
    while(queue.size()!=0){
        queue.front()->calculate();
        delete(queue.front());
        queue.pop_front();
    }
    //close sockets
    close(cnctfd);
    close(servfd);
    exit(0);
}
int Reader::takeLoop (vector<vector<string>> *allLines,int k){
    int count=0;
    // { in this line
    if(allLines->at(k).at(allLines->at(k).size()-1)=="{")
        count++;
    // { in the next line;
    else if(allLines->at(k+1).at(0)=="{"){
        count++;
        k++;
    }
    //only one command
    else{
        return 0;
    }
    for(int i =k+1;i<=allLines->size();i++){
        for(int j=0;j<allLines->at(i).size();j++){
            if(allLines->at(i).at(j)=="{")
                count++;
            if(allLines->at(i).at(j)=="}")
                count--;
            if(count==0){
                return i;
            }
        }
    }
    //invalid number of { }
    if (count!=0)
        return -1;
}
void Reader::fillMap(){
    SymbolTable *st=new SymbolTable();
    st->initPath();
    this->st=st;

}
SymbolTable* Reader::getSt(){
    return this->st;
}

parserParams* Reader::parser(vector<vector<string>> *allLines,int i){

    parserParams * par=new parserParams();
    int a=i;
    vector<string> vec=allLines->at(i);
    int x;
    vector<Expression*>commands;
    string command=vec.at(0);
    if(command=="openDataServer"){
        par->exp=new CommandExpression(new OpenServerCommand(),st,vec);
        par->i=1;
        return par;
    }
    else if(command=="connect"){
        par->exp=new CommandExpression(new ConnectCommand(),st,vec);
        par->i=1;
        return par;
    }
    else if(command=="var"){
        par->exp=new CommandExpression(new DefineVarCommand(),st,vec);
        par->i=1;
        return par;
    }
    else if(command=="print"){
        par->exp=new CommandExpression(new PrintCommand(),st,vec);
        par->i=1;
        return par;
    }else if(command=="sleep"){
        par->exp=new CommandExpression(new SleepCommand(),st,vec);
        par->i=1;
        return par;
    }
    else if(vec.at(0)=="while"){
        x=takeLoop(allLines,i);
        if(x==0){
            commands.push_back(parser(allLines,i+1)->exp);
        }
        while(i<x) {
            parserParams * par1=parser(allLines, i + 1);
            Expression* ex=par1->exp;
            if(ex!= nullptr)
                commands.push_back(ex);
            i=i+par1->i;
            delete par1;
        }
        par->exp=new CommandExpression(new LoopCommand(commands),st,vec);
        par->i=x+1-a;
        return par;
    }else if(vec.at(0)=="if"){
        x=takeLoop(allLines,i);
        if(x==0){
            commands.push_back(parser(allLines,i+1)->exp);
        }
        if(x!=-1){
            while(i<x) {
                parserParams * par1=parser(allLines, i + 1);
                Expression* ex=par1->exp;
                if(ex!= nullptr)
                    commands.push_back(ex);
                i=i+par1->i;
                delete par1;
            }
        }
        par->exp=new CommandExpression(new IfCommand(commands),st,vec);
        par->i=x+1-a;
        return par;
    }
    // a = b
    else if(vec.size()!=1){
        par->exp=new CommandExpression(new Setter(),st,vec);
        par->i=1;
        return par;
    } else{
        par->exp= nullptr;
        par->i=1;
        return par;
    }
}
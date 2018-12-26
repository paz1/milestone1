//
// Created by paz on 18/12/18.
//

#include "ConditionParser.h"
#include "ExpressionCreator.h"
ConditionParser::ConditionParser(vector<Expression *> commands) {
    this->commands=commands;
}
void ConditionParser::doCommand(vector<string> vec, SymbolTable *st) {
    string s=vec.at(1);
    string a,b;
    string cond;
    //seperate to a op b
    if(s.find("<=")!=string::npos){
        long p=s.find("<=");
        cond="<=";
        long i=0;
        while(i<p){
            a=a+s.at(i);
            i++;
        }
        i=p+2;
        while(i<s.size()){
            b=b+s.at(i);
            i++;
        }
    }
    if(s.find(">=")!=string::npos){
        long p=s.find(">=");
        cond=">=";
        long i=0;
        while(i<p){
            a=a+s.at(i);
            i++;
        }
        i=p+2;
        while(i<s.size()){
            b=b+s.at(i);
            i++;
        }
    }
    if(s.find("==")!=string::npos){
        long p=s.find("==");
        cond="==";
        long i=0;
        while(i<p){
            a=a+s.at(i);
            i++;
        }
        i=p+2;
        while(i<s.size()){
            b=b+s.at(i);
            i++;
        }
    }
    if(s.find("!=")!=string::npos){
        long p=s.find("!=");
        cond="!=";
        long i=0;
        while(i<p){
            a=a+s.at(i);
            i++;
        }
        i=p+2;
        while(i<s.size()){
            b=b+s.at(i);
            i++;
        }
    }
    if(s.find("<")!=string::npos){
        long p=s.find("<");
        cond="<";
        long i=0;
        while(i<p){
            a=a+s.at(i);
            i++;
        }
        i=p+1;
        while(i<s.size()){
            b=b+s.at(i);
            i++;
        }
    }
    if(s.find(">")!=string::npos){
        long p=s.find(">");
        cond=">";
        long i=0;
        while(i<p){
            a=a+s.at(i);
            i++;
        }
        i=p+1;
        while(i<s.size()){
            b=b+s.at(i);
            i++;
        }
    }
    Expression *exp1=ExpressionCreator::createExpression(a,st);
    Expression *exp2=ExpressionCreator::createExpression(b,st);
    double num1 =exp1->calculate();
    double num2 =exp2->calculate();
    delete(exp1);
    delete(exp2);

    this->flag = false;
    if (cond == ">") {
        if (num1 > num2)
            this->flag=true;
    }
    else if (cond == "<") {
        if (num1 < num2)
            this->flag=true;
    }
    else if (cond == ">=") {
        if (num1 >= num2)
            this->flag=true;
    }
    else if (cond == "<=") {
        if (num1 <= num2)
            this->flag=true;

    }
    else if (cond == "==") {
        if (num1 == num2)
            this->flag=true;
    }
    else if (vec.at(2) == "!=") {
        if (num1 != num2)
            this->flag=true;
    }
}
ConditionParser::~ConditionParser() {
    for(Expression* exp:commands){
        delete(exp);
    }
}
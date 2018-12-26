//
// Created by paz on 17/12/18.
//

#ifndef MILESTONE1_LEXER_H
#define MILESTONE1_LEXER_H

#include <vector>
#include <string>
#include <map>
#include "Command.h"
#include "Expression.h"
#include "SymbolTable.h"

using namespace std;
struct parserParams{
    Expression * exp;
    int i;
};
class Reader {
private:
    int isConditionalBlock(string s);
    vector<string> connectLexer(string s, SymbolTable* st);
    vector<string> sleepLexer(string s, SymbolTable* st);
    vector<string> printLexer(string s, SymbolTable* st);
    vector<string> assignLexer(string s, SymbolTable* st);
    vector<string> openServerLexer(string s,SymbolTable* st);
    SymbolTable* st;
public:
    static void cutSpaces(string* s);
    vector<string> separateExpressions(string line);
    vector<string> lineLexer(string s/*, SymbolTable* st*/);

    SymbolTable * getSt();
    parserParams* parser(vector<vector<string>> *allLines,int i);
    int takeLoop (vector<vector<string>> *allLines,int k);
    void apply(string str);
    void fillMap();
};


#endif //MILESTONE1_LEXER_H

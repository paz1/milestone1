//
// Created by sara on 18/12/18.
//

#ifndef MILESTONE1_EXPRESSIONCREATOR_H
#define MILESTONE1_EXPRESSIONCREATOR_H

#include <string>
#include <stack>
#include <queue>
#include <list>
#include <regex>
#include "Expression.h"
#include "Div.h"
#include "Plus.h"
#include "Mult.h"
#include "Minus.h"
#include "SymbolTable.h"

using namespace std;
class ExpressionCreator {
   static vector<string> convertToNumExp(string s, SymbolTable* ST);
    static deque<string> infixToPostfix(string exp);
    static BinaryExpression* createBinaryExp(string sign);
    static Expression* postfixToExp(deque<string> queueExp);
public:
    static bool isNumber(string s);
    static bool isOperator(char c);
    static bool isLetter(char c);
    static vector<string> findVars(string s);
/*    static vector<string> convertToNumExp(string s, SymbolTable* ST); //TODO:delete - method should be private
    static deque<string> infixToPostfix(string exp); //TODO:delete - method should be private*/
    static Expression* createExpression(string s, SymbolTable* ST);

};


#endif //MILESTONE1_EXPRESSIONCREATOR_H
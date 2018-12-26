//
// Created by sara on 18/12/18.
//

#include "ExpressionCreator.h"
#include "Reader.h"


bool ExpressionCreator::isOperator(char c){
    return ((c == '+')|| (c == '-')
            || (c == '*') || (c == '/'));
}
bool ExpressionCreator::isNumber(string s) {
    string doubleFormat = "[-]?[0-9]+[.]?[0-9]*";
    regex numSequence(doubleFormat);
    smatch var;
    regex_match(s, var, numSequence);
    return !var.empty();
}
deque<string> ExpressionCreator::infixToPostfix(string exp){
    stack<string> stack;
    deque<string> queue;
    int flag = 0;
    for(int i = 0; i < exp.length(); i++){
        char c = exp[i];

        if(c == '('){
            flag++;
            stack.push("(");
        } else if(c == ')'){
            if(flag){
                vector<string> subExp;
                subExp.push_back(stack.top());
                // push all there is in the middle to the queue and pop from stack
                while(stack.top() != "("){
                    if(stack.top()[0] == '!'){
                        queue.push_back("-");
                    } else {
                        queue.push_back(stack.top());
                    }
                    stack.pop();
                }
                stack.pop();
            } else {
                __throw_logic_error("Can't have ')' without '('");
            }

        } else if(isOperator(c)){
            if(c == '+' || c == '-') {

                if(c == '-'){
                    if(i==0){
                        queue.push_back("0");
                        stack.push("!");
                        continue;
                    } else if(isOperator(exp[i-1]) || exp[i-1] == '('){
                        queue.push_back("0");
                        stack.push("!");
                        continue;
                    }
                }

                while (!stack.empty() && (stack.top() == "*" || stack.top() == "/" || stack.top() == "!")){
                    if(stack.top() == "!"){
                        queue.push_back("-");
                    } else {
                        queue.push_back(stack.top());
                    }
                    stack.pop();
                }

            }
            stack.push(string(1, c));
        } else if(('0'<=c && c<='9')|| c == '.') {
            string num;
            while((('0'<=c && c<='9')|| c == '.') && (i<exp.length())){
                num += string(1,exp[i]);
                if(i+1<exp.length() && (exp[i+1] > '9' || '0' > exp[i+1]) && exp[i+1]!='.'){//todo: dot is good?
                    break;
                }
                i++;
            }
            queue.push_back(num);
        }
    }
    while(!stack.empty()){
        if(stack.top() == "!"){
            queue.push_back("-");
        } else {
            queue.push_back(stack.top());
        }
        stack.pop();
    }
    return queue;
}
BinaryExpression* ExpressionCreator::createBinaryExp(string sign){
    char c = sign[0];
    if(c == '+'){
        return new Plus();
    } else if(c == '-'){
        return new Minus();
    } else if(c == '/'){
        return new Div();
    } else if(c == '*'){
        return new Mult();
    }
}
Expression* ExpressionCreator::postfixToExp(deque<string> queueExp){
    stack<Expression*> stack;
    while(!queueExp.empty()){
        if(queueExp.size() == 1 && queueExp.at(0)[0] == '&'){
            Expression* mainExp = stack.top();
            stack.pop();
            queueExp.pop_front();
            return mainExp;
        }
        int i = 0;
        //go forward until finding an operator
        while(!queueExp.empty() && !isOperator(queueExp.at(i)[0])){
            i++;
        }
        BinaryExpression* exp = ExpressionCreator::createBinaryExp(queueExp.at(i));
        // if there isn't a number
        if(queueExp.at(i-1)[0] == '&'){
            //pop from stack last expression that was pushed- it's the right child
            exp->setRight(stack.top());
            stack.pop();
            //queueExp.erase(queueExp.begin() + (i-1));
        } else {
            exp->setRight(new Number(stod(queueExp.at(i-1))));
        }
        // if there isn't a number
        if(queueExp.at(i-2)[0] == '&'){
            //pop from stack last expression that was pushed- it's the left child
            exp->setLeft(stack.top());
            stack.pop();
            //queueExp.erase(queueExp.begin() + (i-2));
        } else {
            exp->setLeft(new Number(stod(queueExp.at(i-2))));
        }
        stack.push(exp);
        queueExp.erase(queueExp.begin() + i);
        queueExp.erase(queueExp.begin() + (i-1));
        queueExp[i-2]= "&";
    }
    if(stack.empty()){
        return nullptr;
    }
    Expression* mainExp = stack.top(); //TODO: check how to respond to stack empty
    return mainExp;
}
Expression* ExpressionCreator::createExpression(string s, SymbolTable* ST){
    string infix;
    vector<string> temp = convertToNumExp(s,ST);
    for(string s: temp){
        infix += s;
    }
    Reader::cutSpaces(&infix);

    if(isNumber(infix)){
        return new Number(stod(infix));
    }
    deque<string> queueExp = infixToPostfix(infix);

    Expression* expression = postfixToExp(queueExp);
    return expression;
}
bool isVar(char c){
    return (('a'<= c  && c <= 'z')||('A'<= c  && c <= 'Z')
            ||('0'<= c  && c <= '9')|| c == '_');
}
bool ExpressionCreator::isLetter(char c){
    string cha = "[a-zA-Z]";
    string myChar(1,c);
    regex legalVar(cha);
    smatch var;
    regex_match(myChar, var, legalVar);
    return !var.empty();
}
vector<string> ExpressionCreator::findVars(string s){
    vector<string> vec;
    string var;
    for(int i =0; i < s.length(); i++){
        while(isLetter(s[i])|| s[i]=='_'||isdigit(s[i])!=0){
            if(var.empty()&&isdigit(s[i])!=0){
                i++;
                continue;
            } else {
                var+=s[i];
            }
            i++;
        }
        if(!var.empty()){
            vec.push_back(var);
        }
        var.clear();
    }
    return vec;
}
vector<string> ExpressionCreator::convertToNumExp(string s, SymbolTable* ST){
    vector<string> vec;
    if(isNumber(s)){
        vec.push_back(s);
        return vec;
    }
    vec = findVars(s);
    for(string var:vec){
        //if(var.)
        size_t startVar = s.find(var);
        while(startVar!=string::npos){
            s.replace(startVar, var.length(),to_string(ST->getVarValue(var)));
            startVar = s.find(var);
        }
    }
    vec.clear();
    vec.push_back(s);
    /*string newExpStr;
    for(int i = 0; i<s.length(); i++){
        if(('0'<= s[i] && s[i] <= '9')|| isOperator(s[i])){
            newExpStr += s[i];
            continue;
        }
        if(!isVar(s[i])){
            continue;
        }
        string var;
        while(isVar(s[i])){
            var += s[i];
            i++;
        }
        if(!var.empty()){
            double val = ST.getValue(var);
            newExpStr += to_string(val);
        }
    }*/
    return vec;
}
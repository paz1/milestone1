//
// Created by paz on 18/12/18.
//

#ifndef MILESTONE1_SYMBOLTABLE_H
#define MILESTONE1_SYMBOLTABLE_H
#include <vector>

#include <string>
#include <map>

using namespace std;

class SymbolTable {
    // var-value
    map<string, double> varsMap;
    // path-value
    map<string, double> dataMap;
    // var bind path
    map<string, string> bindMap;
public:
    void initx();

    void setVarValue(string str, double value);

    double getVarValue(string key);

    bool hasVarValue(string key);

    void initPathValues(string str);

    double getPathValue(string str);

    void initPath();

    // s1=var s2=path
    void setBind(string s1, string s2);

    string getBindPath(string s);

    bool hasBindPath(string s);

    void setPathValue(string path);
    bool hasPath(string key);
    void updateBinds(string path, double val);
    string getSendMessage(string s);
};


#endif //MILESTONE1_SYMBOLTABLE_H

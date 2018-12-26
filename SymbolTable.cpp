//
// Created by paz on 18/12/18.
//

#include <sstream>
#include <cstring>
#include "SymbolTable.h"
void SymbolTable::setVarValue(string str, double value){
    varsMap[str]=value;
}
double SymbolTable::getVarValue(string key) {
    return varsMap.find(key)->second;
}
bool SymbolTable::hasVarValue(string key) {
    if(varsMap.count(key))
        return true;
    return false;
}
//TODO chan
void SymbolTable::initPathValues(string str){
    string path;
    vector<double> vec;
    istringstream line(str);
    string word;
    //if we get more than we need, cut only the data
    if(str.size()>800) {
        getline(line, word, '\n');
    }

    while (getline(line,word,',')){
        if(word.find('\n') != string::npos){
            string c;
            for(int i=0;i<word.length();i++){
                if(word.at(i)!='\n'){
                    c=c+word.at(i);
                }
                if(c.size()!=0)
                {
                    //save the data
                    double x=stod(c);
                    vec.push_back(x);
                    break;
                }
            }
            break;
        }
        if(word.size()!=0&&(word.find('\n') == string::npos)){
        double x=stod(word);
        vec.push_back(x);}
    }
    //update according to the xml- the data
    this->dataMap.at("/instrumentation/airspeed-indicator/indicated-speed-kt")=vec[0];
    this->dataMap.at("/instrumentation/altimeter/indicated-altitude-ft")=vec[1];
    this->dataMap.at("/instrumentation/altimeter/pressure-alt-ft")=vec[2];
    this->dataMap.at("/instrumentation/attitude-indicator/indicated-pitch-deg")=vec[3];
    this->dataMap.at("/instrumentation/attitude-indicator/indicated-roll-deg")=vec[4];
    this->dataMap.at("/instrumentation/attitude-indicator/internal-pitch-deg")=vec[5];
    this->dataMap.at("/instrumentation/attitude-indicator/internal-roll-deg")=vec[6];
    this->dataMap.at("/instrumentation/encoder/indicated-altitude-ft")=vec[7];
    this->dataMap.at("/instrumentation/encoder/pressure-alt-ft")=vec[8];
    this->dataMap.at("/instrumentation/gps/indicated-altitude-ft")=vec[9];
    this->dataMap.at("/instrumentation/gps/indicated-ground-speed-kt")=vec[10];
    this->dataMap.at("/instrumentation/gps/indicated-vertical-speed")=vec[11];
    this->dataMap.at("/instrumentation/heading-indicator/indicated-heading-deg")=vec[12];
    this->dataMap.at("/instrumentation/magnetic-compass/indicated-heading-deg")=vec[13];
    this->dataMap.at("/instrumentation/slip-skid-ball/indicated-slip-skid")=vec[14];
    this->dataMap.at("/instrumentation/turn-indicator/indicated-turn-rate")=vec[15];
    this->dataMap.at("/instrumentation/vertical-speed-indicator/indicated-speed-fpm")=vec[16];
    this->dataMap.at("/controls/flight/aileron")=vec[17];
    this->dataMap.at("/controls/flight/elevator")=vec[18];
    this->dataMap.at("/controls/flight/rudder")=vec[19];
    this->dataMap.at("/controls/flight/flaps")=vec[20];
    this->dataMap.at("/controls/engines/current-engine/throttle")=vec[21];
    this->dataMap.at("/engines/engine/rpm")=vec[22];
    for(std::map<string,double>::iterator it = this->varsMap.begin();
        it != this->varsMap.end(); ++it){
        if(hasBindPath((*it).first))
            (*it).second=getPathValue(getBindPath((*it).first));
    }
}
void SymbolTable::updateBinds(string path,double val){
    for (std::map<string,string>::iterator it = this->bindMap.begin();
         it != this->bindMap.end(); ++it){
        if((*it).second==path){
            this->setVarValue((*it).first,val);
        }
    }
}
double SymbolTable::getPathValue(string key) {
    return dataMap.at(key);
}
bool SymbolTable::hasPath(string key){
    if(dataMap.count(key)){
        return true;
    }
    return false;
}
void SymbolTable::initPath(){
    this->dataMap["/instrumentation/airspeed-indicator/indicated-speed-kt"]=0;
    this->dataMap["/instrumentation/altimeter/indicated-altitude-ft"]=0;
    this->dataMap["/instrumentation/altimeter/pressure-alt-ft"]=0;
    this->dataMap["/instrumentation/attitude-indicator/indicated-pitch-deg"]=0;
    this->dataMap["/instrumentation/attitude-indicator/indicated-roll-deg"]=0;
    this->dataMap["/instrumentation/attitude-indicator/internal-pitch-deg"]=0;
    this->dataMap["/instrumentation/attitude-indicator/internal-roll-deg"]=0;
    this->dataMap["/instrumentation/encoder/indicated-altitude-ft"]=0;
    this->dataMap["/instrumentation/encoder/pressure-alt-ft"]=0;
    this->dataMap["/instrumentation/gps/indicated-altitude-ft"]=0;
    this->dataMap["/instrumentation/gps/indicated-ground-speed-kt"]=0;
    this->dataMap["/instrumentation/gps/indicated-vertical-speed"]=0;
    this->dataMap["/instrumentation/heading-indicator/indicated-heading-deg"]=0;
    this->dataMap["/instrumentation/magnetic-compass/indicated-heading-deg"]=0;
    this->dataMap["/instrumentation/slip-skid-ball/indicated-slip-skid"]=0;
    this->dataMap["/instrumentation/turn-indicator/indicated-turn-rate"]=0;
    this->dataMap["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"]=0;
    this->dataMap["/controls/flight/aileron"]=0;
    this->dataMap["/controls/flight/elevator"]=0;
    this->dataMap["/controls/flight/rudder"]=0;
    this->dataMap["/controls/flight/flaps"]=0;
    this->dataMap["/controls/engines/current-engine/throttle"]=0;
    this->dataMap["/engines/engine/rpm"]=0;

}

void SymbolTable::setBind(string s1,string s2){
    this->bindMap[s1]=s2;
}
void SymbolTable::setPathValue(string path){
    this->dataMap[path]=0;
}
bool SymbolTable::hasBindPath(string s){
    if(bindMap.count(s))
        return true;
    return false;
}
string SymbolTable::getBindPath(string s){
    return bindMap.find(s)->second;
}
string SymbolTable::getSendMessage(string s){

    return  "set " + s + " " + to_string(this->dataMap.at(s));

}

//
// Created by paz on 16/12/18.
//

#include <tgmath.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "OpenServerCommand.h"
#include "ExpressionCreator.h"
#include <pthread.h>
#include <iostream>
#include <thread>

int ifConectServ=0;
int servfd=-1;
//extern pthread_mutex_t mutex;
//extern pthread_t trid;

struct MyParams
{
    int fd;
    SymbolTable* st;
    OpenServerCommand openServerCommand;
};
void* thread_func(void* arg)
{
    struct MyParams* params = (struct MyParams*) arg;
    //open new server
    params->openServerCommand.readData(params->fd,params->st);
    delete params;
    return nullptr;
}
void OpenServerCommand::doCommand(vector<string> vec,SymbolTable* st) {
    checkIsValid(vec);
    int fd=openNewServer(vec,st);
    struct MyParams* params = new MyParams();

    //open thread
    params->fd = fd;
    params->st = st;
    params->openServerCommand=*this;
    pthread_t trid;
    pthread_create(&trid, nullptr, thread_func, params);
    return;
}


int OpenServerCommand::openNewServer(vector<string> vec,SymbolTable* st){
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        __throw_invalid_argument("ERROR opening socket");
    servfd=sockfd;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    Expression* exp=ExpressionCreator::createExpression(vec.at(1),st);
    portno = exp->calculate();
    delete(exp);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        __throw_invalid_argument("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
    if (newsockfd < 0)
        __throw_invalid_argument("ERROR on accept");
    return newsockfd;

}
void OpenServerCommand::readData(int fd,SymbolTable* st){
    int s=1000;
    char buffer[1000]={0};
    int i=0;
    while(true){
        //pthread_mutex_lock(&mutex);

        read( fd , buffer, s);
        if(ifConectServ==0){
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
            ::ifConectServ=1;
        }
        i++;
        st->initPathValues(buffer);
        //bzero(buffer,1000);
        //pthread_mutex_unlock(&mutex);
    }
}



void OpenServerCommand::checkIsValid(vector<string> vec){
    //TODO 2
    if(vec.size()==(2+1)){
        //valid port
        if(stoi(vec.at(1))>(pow(2,16))||stoi(vec.at(1))<0){
            __throw_invalid_argument("no valid port");
        }
    }
    else {
        __throw_invalid_argument("no match parameters");
    }
}
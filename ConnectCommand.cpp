//
// Created by paz on 16/12/18.
//

#include <tgmath.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include "ConnectCommand.h"
#include "ExpressionCreator.h"
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int cnctfd=-1;
extern int ifConectServ;
void ConnectCommand::doCommand(vector<string> vec, SymbolTable *st) {
    checkIsValid(vec);
    //connect to server
    connecting(vec,st);
}

void ConnectCommand::connecting(vector<string> vec, SymbolTable *st) {

    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    Expression* exp=ExpressionCreator::createExpression(vec.at(2),st);
    portno = exp->calculate();
    delete(exp);
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        /*perror("ERROR opening socket");
        exit(1);*/
        __throw_invalid_argument("ERROR opening socket");
    }
    ::cnctfd=sockfd;
    // declaring character array
    char char_array[vec.at(1).size() + 1];
    strcpy(char_array, vec.at(1).c_str());
    server = gethostbyname(char_array);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    //while not open server
    while(ifConectServ==0){}
    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

}
void ConnectCommand::checkIsValid(vector<string> vec) {
    if (vec.size() == (2 + 1)) {
        //valid port
        if (stoi(vec.at(2)) > (pow(2, 16)) || stoi(vec.at(2)) < 0) {
            __throw_invalid_argument("invalid port");
        }
        //valid IP
        vector<string> checkIP;
        istringstream line(vec.at(1));
        string word;
        while (getline(line, word, '.')) {
            checkIP.push_back(word);
        }
        if (checkIP.size() == 4) {
            for (int i = 0; i < 4; i++) {
                if (stoi(checkIP.at(i)) > 255 || stoi(checkIP.at(i)) < 0)
                    __throw_invalid_argument("invalid IP");
            }
        } else {
            __throw_invalid_argument("invalid IP");
        }

    } else {
        __throw_invalid_argument("no match parameters");
    }
}
#include <iostream>
#include "Reader.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"

using namespace std;
//pthread_mutex_t mutex;
//pthread_t trid;

int main(int argc, char** argv) {
    Reader r;
    r.apply(argv[1]);
/*Reader r;
r.fillMap();
   vector<string> vec={"connect" ,"5400", "10"};
    OpenServerCommand c;
    c.doCommand(vec,r.getSt());
    pthread_join(trid, nullptr);*/
    return 0;

}

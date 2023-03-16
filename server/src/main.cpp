// in the name of God

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h> 
#include <signal.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include<unistd.h>
#include<map>

#include "../inc/manual.hpp"
#include "../inc/dashboard.hpp"
#include "../inc/server.hpp"

using namespace std;

map<int,string> Info::status =  Info::create_map();

int main(int argc, char const *argv[]) 
{
    Dashboard dashboard;
    Server server(& dashboard);
    server.startServer();
    return 0;
}
#ifndef __SERVER_HPP__
#define __SERVER_HPP__

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
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include "dashboard.hpp"

class Server
{

public:
    Server(Dashboard *dashboard);
    void start();
    void run();

private:
    int serverPort;
    std::string serverIP;
    Dashboard *dashboard;
    int setupServer(int port); 
    int acceptClient(int serverFd);

    int serverFd;
    fd_set masterSet;
    fd_set workingSet;
    int maxSd;
    
};
#endif
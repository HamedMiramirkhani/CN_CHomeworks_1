#pragma once

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

#include "manual.hpp"
#include "dashboard.hpp"

class Server
{

public:
    Server(Dashboard *dashboard);
    void startServer();
    void set_fd_set();
    void runServer();

private:
    int serverPort;
    std::string serverIp;
    Dashboard *dashboard;
    int setupServer(int port); 
    int accept_client(int serverFd);

    int serverFd;
    fd_set master_set;
    fd_set working_set;
    int max_sd;
    
};

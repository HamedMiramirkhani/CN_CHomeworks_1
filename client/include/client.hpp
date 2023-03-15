#ifndef __CLIENT_H__
#define __CLIENT_H__
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h> 
#include <signal.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include<unistd.h>

#include "userManual.hpp"

class Client
{
public:
    Client();
    void start();
    void sendRequest();
    void connectServer(int port, const char* ip);

private:
    int serverFd;
    fd_set master_set;
    fd_set working_set;
    int maxSd;
};

#endif
#pragma once

#include "help.hpp"
#include "manager.hpp"
#include "logger.hpp"

class Server
{
public:
    Server(Manager *manager);
    void start();
    void run();
private:
    FileDataContainers::config read_config(std::string path);
    int setup(int port); 
    int accept_client(int server_fd);
    
    Logger logger;
    int server_port;
    std::string server_ip;
    Manager *manager;
    int server_fd;
    fd_set master_set;
    fd_set working_set;
    int max_sd;
};

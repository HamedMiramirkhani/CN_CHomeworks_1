#pragma once

#include "manual.hpp"
#include "cli.hpp"

class Client
{
public:
    Client();
    void start();
    int connect_to_server(const int port, const char* ip);
    void send_requests();

private:
    Config read_config(std::string path);
    Cli cli;
    int server_fd;
    fd_set master_set;
    fd_set working_set;
    int max_sd;
};

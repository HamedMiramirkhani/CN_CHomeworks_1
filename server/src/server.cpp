// In the Name of God

#include "server.hpp"

#include <iostream>

using namespace std;

Server::Server(Dashboard *dashboard)
    :
    dashboard(dashboard),
    server_fd(NOT_CONNECTED),
    max_sd(0)
{
    serverPort = 8181;
    serverIP = "127.0.0.1";
}

void Server::start() 
{
    serverFd = setupServer(serverPort);
    maxSd = serverFd;
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    FD_SET(STD_IN, &master_set);
    run();
}

void Server::run()
{
    while (1) 
    {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);

        for(int i = 0; i <= max_sd; i++) 
        {
            if (FD_ISSET(i, &working_set)) 
            {    
                if (i == server_fd) // new clinet
                {  
                    int new_client_fd = acceptClient(server_fd);
                    FD_SET(new_client_fd, &master_set);
                    if (new_client_fd > max_sd)
                        max_sd = new_client_fd;
                    //dashboard->add_new_client(new_client_fd);
                }

                else if (i == STD_IN) //input buffer
                {
                    char command[MAX_STRING_SIZE] = {0};
                    int last_char = read(STD_IN, command, MAX_STRING_SIZE);
                }
                
                else // client sending msg
                { 

                    
                }
            }
        }
    }
}

int Server::setupServer(int port)
{
    struct sockaddr_in address;
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 4);
    return server_fd;
}

int Server::acceptClient(int server_fd)
{
    int client_fd;
    struct sockaddr_in clientAddress;
    int addressLen = sizeof(clientAddress);
    clientFd = accept(serverFd, (struct sockaddr *)&clientAddress, (socklen_t*) &addressLen);
    return clientFd;
}
// In the Name of God

#include "../inc/server.hpp"
#include "../inc/manual.hpp"

#include <iostream>

using namespace std;

Server::Server(Dashboard *dashboard)
    :
    dashboard(dashboard),
    serverFd(NOT_CONNECTED),
    max_sd(0)
{
    serverPort = 8181;
    serverIp = "127.0.0.1";
}

void Server::startServer() 
{
    serverFd = setupServer(serverPort);
    max_sd = serverFd;
    FD_ZERO(&master_set);
    FD_SET(serverFd, &master_set);
    FD_SET(STD_IN, &master_set);
    runServer();
}

void Server::runServer()
{
    while (1) 
    {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);

        for(int i = 0; i <= max_sd; i++) 
        {
            if (FD_ISSET(i, &working_set)) 
            {    
                if (i == serverFd) // new clinet
                {  
                    int new_client_fd = accept_client(serverFd);
                    FD_SET(new_client_fd, &master_set);
                    if (new_client_fd > max_sd)
                        max_sd = new_client_fd;
                    dashboard->addNewClient(new_client_fd);
                }

                else if (i == STD_IN) //input buffer
                {
                    char command[MAX_STRING_SIZE] = {0};
                    int last_char = read(STD_IN, command, MAX_STRING_SIZE);
                    command[last_char - 1] = '\0';
					printf("server-input:: %s\n", command);
                }
                
                else // client sending msg
                { 
                    char command[MAX_STRING_SIZE] = {0};
                    if (recv(i , command, MAX_STRING_SIZE, 0) == 0) 
                    { // EOF
                        printf("***\t client fd = %d closed\t***\n", i);
                        close(i);
                        FD_CLR(i, &master_set);
                        dashboard->connection_closed(i);
                        continue;
                    }
                    // printf("client with fd = %d send %s \n", i, command);
                    dashboard->handle_command(i, string(command));
                    char* response = dashboard->getResponse(i, command);
                    int status = send(i, response, strlen(response), 0);
                    if (status == 0)
                        printf("***\t could not send to client fd = %d\t***\n", i);

                    
                }
            }
        }
    }
}

int Server::setupServer(int port)
{
    struct sockaddr_in address;
    int serverFd;
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(serverIp.c_str());
    address.sin_port = htons(port);

    bind(serverFd, (struct sockaddr *)&address, sizeof(address));
    listen(serverFd, 4);
    return serverFd;
}

int Server::accept_client(int serverFd)
{
    int client_fd;
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    client_fd = accept(serverFd, (struct sockaddr *)&client_address, (socklen_t*) &address_len);
    return client_fd;
}

printf("***\t could not send to client fd = %d\t***\n", i);
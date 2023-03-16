#include "client.hpp"
#include "userManual.hpp"

Client::Client():serverFd(NOT_CONNECTED),max_sd(0)
{}

void Client::start() 
{
    connect(PORT, SERVER_IP);
    FD_ZERO(&master_set);
    FD_SET(STD_IN, &master_set);
    FD_SET(serverFd, &master_set);
    max_sd = serverFd;
    sendRequests();
}

void Client::connect(int port, const char* ip)
{
    struct sockaddr_in server_address;
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr(ip);

    if (connect(serverFd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Error in connecting to server\n");
        exit(EXIT_FAILURE);
    }
}

void Client::sendRequest()
{
    while (1) 
    {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);
        for(int i = 0; i <= max_sd; i++) 
        {
            if (FD_ISSET(i, &working_set)) 
            { 
                if (i == STD_IN) //input buffer
                {
                    char command[MAX_STRING_SIZE] = {0};
                    int last_char = read(STD_IN, command, MAX_STRING_SIZE);
                    command[last_char - 1] = '\0';
                    send(serverFd, command, strlen(command), 0);
                }
                else if (i == serverFd) //server response
                {
                    char respone[MAX_STRING_SIZE];
                    int last_char = recv(serverFd, respone, MAX_STRING_SIZE, 0);
                    respone[last_char] = '\0';
                    printf("server said: %s\n",respone);
                }
                else
                    printf("\n***\tproblem accurd :cant connect to server\t***\n");
            }
        }
    }
}
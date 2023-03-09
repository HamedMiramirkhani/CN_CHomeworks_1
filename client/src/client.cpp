#include "client.hpp"
#include "jsonReader.hpp"
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

Client::Client() {}

char* strToCharArray(const std::string& str)
{
    char charArray[str.length() + 1]; 
	strcpy(charArray, str.c_str());
    return charArray;
}

int connectServer(int port, const std::string& hostName)
{
    char* hostNameArray = strToCharArray(hostName);
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(hostNameArray);
    if (connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cout<<"Error in connecting to server\n";
        return -1;
    }
    return fd;
}

void Client::run() {
    std::ifstream f("config.json");
    json j_config;
    f >> j_config;
    int command_fd = connectServer(j_config["commandChannelPort"], j_config["hostName"]);
    
    std::string command;
    char read_buffer[1024];
    while(std::getline(std::cin, command)) {
        send(command_fd, command.c_str(), command.size(), 0);
        recv(command_fd, read_buffer, sizeof(read_buffer), 0);
        std::cout << read_buffer << std::endl;
    }
}
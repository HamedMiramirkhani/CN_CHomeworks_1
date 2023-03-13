#include "server.hpp"
#include "cmdHandler.hpp"
#include "consts.hpp"

Server::Server(
const std::string& configPath, 
const std::string& roomsPath,
const std::string& userInfoPath) 
:jsonReader(JsonReader(configPath, roomsPath, userInfoPath))
{
    hostName = jsonReader.getHostName();
    commandChannelPort = jsonReader.getCommandChannelPort();
    allUsers = jsonReader.getUsers();
    allRooms = jsonReader.getRooms();
}

int setupServer(int port, const std::string& hostName) 
{
    int opt = 1;
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(hostName.c_str());
    address.sin_port = htons(port);

    bind(serverFd, (struct sockaddr *)&address, sizeof(address));
    listen(serverFd, 4);

    return serverFd;
}

void Server::setServerDate(void)
{
    std::string InDate;
    while (true)
    {
        std::cout << "setTime ";
        std::cin >> InDate;
        if (currentDate.setDate(InDate))
        {
            break;
        }
        else
        {
            std::cout << termcolor::red << "Error 401: Invalid value!" << termcolor::reset << std::endl;
        }
    }
}

void Server::handleConnection(int fdSocket)
{
    CmdHandler* commandHandler = new CmdHandler();

    fd_set masterSet, workingSet;
    FD_ZERO(&masterSet);
    FD_ZERO(&workingSet);
    FD_SET(fdSocket, &masterSet);

    int returnSelect;
    int maxFd = fdSocket;

    char readBuffer[1024];
    memset(readBuffer, 0, sizeof(readBuffer));
    char writeBuffer[1024];
    memset(writeBuffer, 0, sizeof(writeBuffer));

    while(true)
    {
        workingSet = masterSet;       
        returnSelect = select(maxFd + 1, &workingSet, NULL, NULL, NULL);
        if (returnSelect < 0)
        {
            std::cerr << "Error in select" << std::endl;
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i <= maxFd; i++)
        { 
            if (FD_ISSET(i, &workingSet))
            {
                if (i == fdSocket) // new connection
                {
                    int newSocket = accept(fdSocket, NULL, NULL);
                    FD_SET(newSocket, &masterSet);
                    if (newSocket > maxFd)
                    {
                        maxFd = newSocket;
                    }
                }
                else // existing connection
                {
                    int EOFrecv = recv(i, readBuffer, sizeof(readBuffer), 0);
                    if (EOFrecv == 0)
                    { // client disconnected
                        std::cout << "Client " << i << " disconnected" << std::endl;
                        close(i);
                        FD_CLR(i, &masterSet);
                    }
                    else
                    {
                        commandHandler->runCommand(i, readBuffer);

                        // send message to client
                        std::string message = "Hello Client " + std::to_string(i);
                        strcpy(writeBuffer, message.c_str());
                        send(i, writeBuffer, sizeof(writeBuffer), 0);

                        // clear buffers
                        memset(writeBuffer, 0, sizeof(writeBuffer));
                        memset(readBuffer, 0, sizeof(readBuffer));
                    }
                }
                break;
            }
        }
    }
}

void Server::run()
{
    int fdSocket = setupServer(commandChannelPort, hostName);

    setServerDate();

    handleConnection(fdSocket);
}
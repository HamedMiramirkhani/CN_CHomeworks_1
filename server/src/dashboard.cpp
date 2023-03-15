// In the Name of God

#include "dashboard.hpp"

using namespace std;

Dashboard::Dashboard(/* args */)
{}

char *Dashboard::getResponse(int client_fd, char *request)
{
    char* response = new char[256];
    strcat(response, "khob\n");
    try
    {
        throw Error(451);
        strcat(response, "-response to client\n");
    }
    catch(Error& e)
    {
        strcat(response, "error massege\n");
    }
    return response;
}

bool Dashboard::connectionClosed(int clientFd)
{
    return false;
}

void Dashboard::addNewClient(int clientFd)
{
    printf("New client connected.fd=%d", clientFd);
    send(clientFd, "\twelcome!", 15, 0);
    usersFdMap[clientFd] = nullptr;
}


unordered_map<string, func_ptr> Dashboard::getCmdList(int fd)
{
    Person* person = usersFdMap[fd];
    return (person == nullptr) ? unregistered_user_list : person->getCmdList();
}

void Dashboard::handleCommand(int fd, string command)
{
    line = command;
    userFd = fd;
    string command_key = Utils::splitLine(command, ' ');
    try
    {
        auto command_list = getCmdList(user_fd);
        //sth
    } 
    catch (Error& error) 
    {
        write(1, error.what().c_str(),strlen(error.what().c_str()));
        write(1, "\n",strlen("\n"));
    }
}




#include "server.hpp"
#include "cmdHandler.hpp"

Server::Server(const std::string& config_path, const std::string& rooms_path,
 const std::string& user_info_path)
    :
    jsonReader(JsonReader(config_path, rooms_path, user_info_path))
{
    hostName = jsonReader.getHostName();
    commandChannelPort = jsonReader.getCommandChannelPort();
}

void* handleConnection() {
    //using cmdHandler check connection between client & server
    CmdHandler* commandHandler = new CmdHandler();

    while (true) {
        //get commands from channels and call commandHandler->runCommand()
    }
}


void Server::run() {
    //socket
    
    while (true) {
        // connections
        // thread
        // handle connection
    }
}
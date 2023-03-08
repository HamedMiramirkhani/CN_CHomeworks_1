#include "server.hpp"
#include "cmdHandler.hpp"
#include <sys/socket.h>
#include <netinet/in.h>

Server::Server(const std::string& config_path, const std::string& rooms_path,
 const std::string& user_info_path)
    :
    jsonReader(JsonReader(config_path, rooms_path, user_info_path))
{
    hostName = jsonReader.getHostName();
    commandChannelPort = jsonReader.getCommandChannelPort();
    allUsers = jsonReader.getUsers();
    allRooms = jsonReader.getRooms();
}

struct sockaddr_in initialSocket(const int port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}

int setupServer(int port) {
    struct sockaddr_in address = initialSocket(port);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 4);
    return server_fd;
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
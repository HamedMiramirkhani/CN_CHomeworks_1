#include "server.hpp"
#include "cmdHandler.hpp"
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
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

struct sockaddr_in initialSocket(const int port,const std::string& hostName) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(hostName.c_str());
    address.sin_port = htons(port);
    return address;
}

int setupServer(int port,const std::string& hostName) {
    struct sockaddr_in address = initialSocket(port, hostName);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 8);
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
    
    int fd_socket = setupServer(commandChannelPort, hostName);

    fd_set master_set, working_set;
    FD_ZERO(&master_set);
    FD_ZERO(&working_set);
    FD_SET(fd_socket, &master_set);
    int max_fd = fd_socket;
    int return_select;
    

    while(true)
    {
        working_set = master_set;       
        return_select = select(max_fd + 1, &working_set, NULL, NULL, NULL);
        if (return_select < 0) {
            std::cerr << "Error in select" << std::endl;
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i <= max_fd; i++) {

            ///check this next time 
            if (FD_ISSET(i, &working_set)) {
                if (i == fd_socket) {
                    int new_socket = accept(fd_socket, NULL, NULL);
                    FD_SET(new_socket, &master_set);
                    if (new_socket > max_fd) {
                        max_fd = new_socket;
                    }
                }
                else {
                    //handle connection
                }
            }
            ///check this next time 
        }
    }
}
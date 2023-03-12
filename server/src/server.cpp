#include "server.hpp"
#include "cmdHandler.hpp"
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
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



void Server::setServerDate(void)
{
    std::string In_date;
    while (true)
    {
        std::cout << "setTime ";
        std::cin >> In_date;
        if (CurrentDate.setDate(In_date))
        {
            break;
        }
        else
        {
            std::cout << termcolor::red << "Error 401: Invalid value!" << termcolor::reset << std::endl;
        }
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
    
    char read_buffer[1024];
    memset(read_buffer, 0, sizeof(read_buffer));

    char write_buffer[1024];
    memset(write_buffer, 0, sizeof(write_buffer));

    setServerDate();

    while(true) {
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
                    int EOF_recv = recv(i, read_buffer, sizeof(read_buffer), 0);
                    if (EOF_recv == 0) { // client disconnected
                        std::cout << "Client " << i << " disconnected" << std::endl;
                        close(i);
                        FD_CLR(i, &master_set);
                    }
                    else {
                        // print client i sent message
                        std::cout << "Client " << i << " sent message: ";
                        std::cout << read_buffer << std::endl; 
                        memset(read_buffer, 0, sizeof(read_buffer));
                        // send message to client i
                        std::string message = "Hello Client " + std::to_string(i);
                        strcpy(write_buffer, message.c_str());
                        send(i, write_buffer, sizeof(write_buffer), 0);
                        memset(write_buffer, 0, sizeof(write_buffer));
                    }
                }
            }
            ///check this next time 
        }
    }
}
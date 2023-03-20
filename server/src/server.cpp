#include "server.hpp"
#include "manual.hpp"

using namespace std;

Server::Server(Manager *manager)
    :
    logger(Logger()), manager(manager),
    server_fd(NOT_CONNECTED), max_sd(0)
{
    FileDataContainers::config config = read_config(Paths::CONFIG_SERVER_DATA_PATH);
    server_port = config.commandChannelPort;
    server_ip = config.hostName;
}

FileDataContainers::config Server::read_config(string path)
{
    ifstream input_file(path, ifstream::binary);
    Json::Value root;
    input_file >> root;

    FileDataContainers::config config;
    for(auto line = root.begin(); line != root.end() ; line++)
    {
        config.hostName = (*line)["hostName"].asString();
        config.commandChannelPort = (*line)["commandChannelPort"].asInt();
    }
    input_file.close();
    return config;
}

void Server::start() 
{
    server_fd = setup(server_port);
    printf("server is running...\n");
    max_sd = server_fd;
    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);
    FD_SET(STD_IN, &master_set);
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
                    int new_client_fd = accept_client(server_fd);
                    FD_SET(new_client_fd, &master_set);
                    if (new_client_fd > max_sd)
                        max_sd = new_client_fd;
                    manager->add_new_client(new_client_fd);
                }

                else if (i == STD_IN) //input buffer
                {
                    char cmd[MAX_STRING_SIZE] = {0};
                    int last_char = read(STD_IN, cmd, MAX_STRING_SIZE);
                    cmd[last_char - 1] = '\0';
                    string server_input = cmd;
                    server_input.push_back(' ');
                    manager->set_today(server_input);
                }
                
                else // client sending msg
                { 
                    char cmd[MAX_STRING_SIZE] = {0};
                    if (recv(i , cmd, MAX_STRING_SIZE, 0) == 0) 
                    { // EOF
                        printf("***\t client fd = %d closed\t***\n", i);
                        close(i);
                        FD_CLR(i, &master_set);
                        continue;
                    }
                    logger.log("User", i, cmd);
                    string response = manager->handle_command(i, string(cmd));
                    logger.log("Server", i, response);
                    send(i, response.c_str(), strlen(response.c_str()), 0);
                }
            }
        }
    }
}

int Server::setup(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(server_ip.c_str());
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	listen(server_fd, MAX_CONNECTIONS);

    return server_fd;
}

int Server::accept_client(int server_fd)
{
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*) &address_len);
    return client_fd;
}

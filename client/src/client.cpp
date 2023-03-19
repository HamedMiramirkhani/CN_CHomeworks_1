#include <iostream>

#include "client.hpp"
#include "errorCMD.hpp"
#include <fstream>

#if __has_include(<jsoncpp/json/json.h>)
# include <jsoncpp/json/json.h>
#elif __has_include(<json/json.h>)
#include <json/json.h>
#endif

using namespace std;

Client::Client() {}

Config Client::read_config(string path)
{
    std::ifstream input_file(path, std::ifstream::binary);
    Json::Value root;
    input_file >> root;

    Config config;
    for(auto line = root.begin(); line != root.end() ; line++)
    {
        config.hostName = (*line)["hostName"].asString();
        config.commandChannelPort = (*line)["commandChannelPort"].asInt();
    }
    return config;
}

void Client::start() 
{
    Config config = read_config(CONFIG_SERVER_DATA_PATH);
    server_fd = connect_to_server(config.commandChannelPort, config.hostName.c_str());
    cli.set_server_fd(server_fd);
    FD_ZERO(&master_set);
    FD_SET(STD_IN, &master_set);
    FD_SET(server_fd, &master_set);
    max_sd = server_fd;
}

int Client::connect_to_server(const int port, const char* ip)
{
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr(ip);

    int new_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(new_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Error in connecting to server\n");
        exit(EXIT_FAILURE);
    }
    return new_fd;
}

void Client::send_requests()
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
                    try {
                        string message = cli.get_input(false);
                        cli.handle_commad(message);
                    }
                    catch (ErrorCMD e) {
                        cout << e.what() << endl;
                        PRINT_INIT_CMD;
                    }
                }
                else if (i == server_fd) //server response
                {
                    char respone[MAX_STRING_SIZE];
                    int last_char = recv(server_fd, respone, MAX_STRING_SIZE, 0);
                    respone[last_char] = '\0';
                    printf("%s\n\n",respone);
                    cli.need_show_menu(respone);
                    PRINT_INIT_CMD;
                }
                else
                    printf("\n%s***\tproblem accurd :cant connect to server\t***%s\n", RED_COLOR, WHITE_COLOR);
            }
        }
    }
}
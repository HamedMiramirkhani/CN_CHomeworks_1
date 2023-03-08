#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include "jsonReader.hpp"
#include <string>


class Server
{
public:
    Server(const std::string& config_path,
            const std::string& rooms_path,
            const std::string& user_info_path);
    void run();

    JsonReader jsonReader;
    int commandChannelPort;
    std::string hostName;
};

#endif
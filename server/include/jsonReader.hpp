#ifndef __JSON_READER_H__
#define __JSON_READER_H__

#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

class JsonReader
{
public:
    JsonReader(const std::string& config_path,
    const std::string& rooms_path,
    const std::string& user_info_path);
    int getCommandChannelPort();
    std::string getHostName();
    
private:
    int commandChannelPort;
    std::string hostName;

    void read(const std::string& config_path,
    const std::string& rooms_path,
    const std::string& user_info_path);
    void readConfig(json j_config);
    void readUserInfo(json j_user);
    void readRoomsInfo(json j_room);
};

#endif
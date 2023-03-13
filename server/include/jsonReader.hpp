#ifndef __JSON_READER_H__
#define __JSON_READER_H__

#include "consts.hpp"
#include "json.hpp"
#include "user.hpp"
#include "room.hpp"

using json = nlohmann::json;

const std::string NOT_QUANTIFIED_STR = "-";
const int NOT_QUANTIFIED_INT = -1;

class JsonReader
{
public:
    JsonReader(const std::string& configPath, const std::string& roomsPath, const std::string& userInfoPath);
    int getCommandChannelPort();
    std::string getHostName();
    std::vector<User*> getUsers();
    std::vector<Room*> getRooms();
    
private:
    void read(const std::string& configPath, const std::string& roomsPath, const std::string& userInfoPath);

    int commandChannelPort;
    std::string hostName;
    void readConfig(json configJson);
    
    void readUserInfo(json userJson);
    std::vector<User*> allUsers;

    void readRoomsInfo(json roomJson);
    std::vector<Room*> allRooms; 
};

#endif
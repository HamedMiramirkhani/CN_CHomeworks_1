#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include "jsonReader.hpp"
#include <string>
#include "date.hpp"
#include "logger.hpp"
#include "termcolor.hpp"

class Server
{
public:
    Server(const std::string& configPath,
            const std::string& roomsPath,
            const std::string& userInfoPath);
    void run();

private:
    JsonReader jsonReader;
    Logger serverLoger;
    int commandChannelPort;
    std::string hostName;
    std::vector<User*> allUsers;
    std::vector<Room*> allRooms; 
    Date currentDate;

    void setServerDate(void);
    void handleConnection(int fdSocket);
};

#endif
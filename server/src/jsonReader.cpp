#include "../include/jsonReader.hpp"

JsonReader::JsonReader(const std::string& configPath,
 const std::string& roomsPath,
 const std::string& userInfoPath
)
{
    read(configPath, roomsPath, userInfoPath);
}

void JsonReader::read(const std::string& configPath,
 const std::string& roomsPath,
 const std::string& userInfoPath) 
 {
    std::ifstream f1(configPath), f2(roomsPath), f3(userInfoPath);
    json configJson, roomJson, userJson;
    f1 >> configJson;
    f2 >> roomJson;
    f3 >> userJson;

    readConfig(configJson);
    readRoomsInfo(roomJson);
    readUserInfo(userJson);
}

void JsonReader::readConfig(json configJson)
{
    commandChannelPort = configJson["commandChannelPort"];
    hostName = configJson["hostName"];
}

void JsonReader::readRoomsInfo(json roomJson)
{
    for (auto& room: roomJson["rooms"])
    {
        int number = stoi(room["number"].get<std::string>());
        int status = room["status"].get<int>();
        int price = room["price"].get<int>();
        int maxCapacity = room["maxCapacity"].get<int>();
        int capacity = room["capacity"].get<int>();
        std::vector<User*> roomUsers = {};
        for (auto& userInRoom: room["users"])
        {
            int id = userInRoom["id"];
            std::string username = NOT_QUANTIFIED_STR;
            std::string password = NOT_QUANTIFIED_STR;
            bool isAdmin = false;
            std::string purse = NOT_QUANTIFIED_STR;
            std::string phoneNumber = NOT_QUANTIFIED_STR;
            std::string address = NOT_QUANTIFIED_STR;
            int numOfBeds = userInRoom["numOfBeds"];
            std::string reserveDate = userInRoom["reserveDate"];
            std::string checkoutDate = userInRoom["checkoutDate"];
            int userRoomNum = number;

            roomUsers.push_back(new User(id, username, password, 
            isAdmin, purse, phoneNumber, address, numOfBeds, 
            reserveDate, checkoutDate, userRoomNum));
        }
        allRooms.push_back(new Room(number, status, price,
         maxCapacity, capacity, roomUsers));
    }
}

void JsonReader::readUserInfo(json userJson)
{
    for (auto& user: userJson["users"])
    {
        int id = user["id"].get<int>();
        std::string username = user["user"].get<std::string>();
        std::string password = user["password"].get<std::string>();
        bool isAdmin = user["admin"].get<std::string>() == "true";
        std::string purse = NOT_QUANTIFIED_STR;
        std::string phoneNumber = NOT_QUANTIFIED_STR;
        std::string address = NOT_QUANTIFIED_STR;
        int numOfBeds = NOT_QUANTIFIED_INT;
        std::string reserveDate = NOT_QUANTIFIED_STR;
        std::string checkoutDate = NOT_QUANTIFIED_STR;
        int userRoomNum = NOT_QUANTIFIED_INT;
        if(!isAdmin)
        {
            purse = user["purse"].get<std::string>();
            phoneNumber = user["phoneNumber"].get<std::string>();
            address = user["address"].get<std::string>();
        }
        User* newUser = new User(id, username, password, isAdmin,
         purse, phoneNumber, address, numOfBeds, 
         reserveDate, checkoutDate, userRoomNum);
        allUsers.push_back(newUser);
    }
}

int JsonReader::getCommandChannelPort()
{ return commandChannelPort; }

std::string JsonReader::getHostName()
{ return hostName; }

std::vector<User*> JsonReader::getUsers()
{ return allUsers; }

std::vector<Room*> JsonReader::getRooms()
{ return allRooms; }

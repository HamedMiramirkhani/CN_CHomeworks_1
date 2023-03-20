#pragma once
//libs
#include <stdio.h>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <memory>
#if __has_include(<jsoncpp/json/json.h>)
# include <jsoncpp/json/json.h>
#elif __has_include(<json/json.h>)
#include <json/json.h>
#endif

//colors
#define RED_COLOR "\x1B[31m"
#define WHITE_COLOR "\x1B[37m"

#include "class_names.hpp"

#define MAX_CONNECTIONS 20
#define MAX_STRING_SIZE 4096
#define NOT_CONNECTED -3
#define STD_IN 0
#define STD_OUT 1

//path
const std::string CONFIG_SERVER_DATA_PATH = "./../json_files/config.json";
const std::string USERS_DATA_PATH = "./../json_files/users.json";
const std::string ROOMS_DATA_PATH = "./../json_files/rooms.json";
const std::string LOG_CLUSTER_PATH = "./../cluster.log";



struct config
{
    std::string hostName;
    int commandChannelPort;
};
struct UserInfo
{
    int id, purse;
    std::string user, password, phoneNumber, address;
    bool admin;
};
struct RentInfo
{
    int id, numOfBeds;
    std::string reserveDate, checkoutDate;
};
struct RoomInfo
{
    int number, status, price, maxCapacity, capacity;
    std::vector<RentInfo> users;
};


struct Info
{
    static std::map<int,std::string> create_map()
    {
        std::map<int,std::string> messages = 
        {
            {101, "DESIRED_ROOM_WAS_NOT_FOUND"},
            {102, "YOUR_RESERVATION_WAS_NOT_FOUND"},
            {103, "YOU_MUST_LEAVE_NOT_CANCEL"},
            {104, "SUCCESSFULLY_ADDED"},
            {105, "SUCCESSFULLY_MODIFIED"},
            {106, "SUCCESSFULLY_DELETED"},
            {108, "YOUR_ACCOUNT_BALANCE_IS_NOT_ENOUGH"},
            {109, "THE_ROOM_CAPACITY_IS_FULL"},
            {110, "SUCCESSFULLY_DONE"},
            {111, "THIS_ROOM_ALREADY_EXISTS"},
            {112, "YOU_ARE_NOT_IN_ROOM_YET"},
            {201, "USER_LOGED_OUT_SUCCESSFULLY"},
            {230, "USER_LOGED_IN"},
            {231, "USER_SUCCESSFULLY_SIGNED_UP"},
            {232, "YOU_LOGED_IN_BEFORE"},
            {311, "USER_SIGNED_UP.ENTER_YOUR -PASS-MONEY-PHONE-ADDR-"},
            {312, "INFORMATION_CHANGED_SUCCESSFULLY"},
            {401, "INVALID_VALUE"},
            {403, "ACCESS_DENIED"},
            {412, "INVALID_CAPACITY_VALUE"},
            {413, "SUCCESSFULLY_LEAVING"},
            {430, "INVALID_USERNAME/PASSWORD"},
            {451, "USER_ALREADY_EXISTS"},
            {503, "BAD_SEQUENCE_OF_COMMANDS"}
        };
        return messages;
    }
    static std::map<int,std::string> status;
};

namespace RoomStatus 
{
    const std::vector<std::string> str_form = {"EMPTY","FULL"};
}
enum room_status
{ EMPTY = 0, FULL = 1 };
enum filter 
{ ENABLE = 1, DISABLE = 0 };

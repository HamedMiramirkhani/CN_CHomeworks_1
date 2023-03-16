#pragma once

#include <iostream>
#include <fstream>
// #include <json/json.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <vector>

#include "../inc/manual.hpp"

class FileHandler
{
public:
    // bool writeInSimpleUserFile(std::vector <SimpleUserInfo> info, std::string path = ..);
    // std::vector <SimpleUserInfo> readFromSimpleUserFile(std::string path = ...);

    // bool writeInAdminUserFile(std::vector <AdminUserInfo> info, std::string path = ..);
    // std::vector <AdminUserInfo> readFromAdminUserFile(std::string path = ..);

    // bool writeInRoomFile(std::vector <RoomInfo> info, std::string path = ..);
    // std::vector <RoomInfo> readFromRoomFile(std::string path = ..);

private:
    Json::Value getTravelerInfo(TravelerInfo traveler);
    Json::Value getDate(Date date);
    std::vector<TravelerInfo> getTravelers(Json::Value root);
    Date getDate(Json::Value root);
};

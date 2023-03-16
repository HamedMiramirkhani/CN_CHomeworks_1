// In the Name of God

#include <iostream>
#include <fstream>
// #include <json/json.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <vector>

#include "../inc/manual.hpp"
#include "../inc/filehandler.hpp"

using namespace std;

bool FileHandler::writeInSimpleUserFile(vector<SimpleUserInfo> info, string path)
{
    Json::Value root; 
    ofstream outputFile(path, ifstream::binary);
    for(auto userInfo : info)
    {
        Json::Value user; 

        user["id"] = userInfo.id;
        user["username"] = userInfo.username;
        user["password"] = userInfo.password;
        user["admin"] = userInfo.admin;
        user["money"] = userInfo.money;
        user["phoneNumber"] = userInfo.phoneNumber;
        user["address"] = userInfo.address;

        root.append(user);
    }
    outputFile << root << endl;
    return true;
}

vector<SimpleUserInfo> FileHandler::readFromSimpleUserFile(string path)
{
    Json::Value root;
    std::ifstream inputFile(path, std::ifstream::binary);
    vector<SimpleUserInfo> info;
    inputFile >> root;

    for(auto user = root.begin(); user != root.end() ; user++)
    {
        SimpleUserInfo userInfo;

        userInfo.id = (*user)["id"].asInt();
        userInfo.username = (*user)["username"].asString();
        userInfo.password = (*user)["password"].asString();
        userInfo.admin = (*user)["admin"].asBool();
        userInfo.money = (*user)["money"].asInt();
        userInfo.phoneNumber = (*user)["phoneNumber"].asString();
        userInfo.address = (*user)["address"].asString();

        info.push_back(userInfo);
    }
    return info;
}

bool FileHandler::writeInAdminUserFile(vector<AdminUserInfo> info, string path)
{
    Json::Value root;
    ofstream outputFile(path, ifstream::binary);
    for(auto userInfo : info)
    {
        Json::Value user; 

        user["id"] = userInfo.id;
        user["username"] = userInfo.username;
        user["password"] = userInfo.password;
        user["admin"] = userInfo.admin;

        root.append(user);
    }
    outputFile << root << endl;
    return true;
}

vector<AdminUserInfo> FileHandler::readFromAdminUserFile(string path)
{
    Json::Value root;
    std::ifstream inputFile(path, std::ifstream::binary);
    vector<AdminUserInfo> info;
    inputFile >> root;

    for(auto user = root.begin(); user != root.end() ; user++)
    {
        AdminUserInfo userInfo;

        userInfo.id = (*user)["id"].asInt();
        userInfo.username = (*user)["username"].asString();
        userInfo.password = (*user)["password"].asString();
        userInfo.admin = (*user)["admin"].asBool();

        info.push_back(userInfo);
    }
    return info;
}

bool FileHandler::writeInRoomFile(vector<RoomInfo> info, string path)
{
    Json::Value root;
    ofstream outputFile(path, ifstream::binary);
    for(auto room_info : info)
    {
        Json::Value room; 

        room["number"] = room_info.number;
        room["status"] = room_info.status;
        room["price"] = room_info.price;
        room["maxCapacity"] = room_info.maxCapacity;
        room["capacity"] = room_info.capacity;

        for(TravelerInfo travelerInfo : room_info.room_residents)
            room["room_residents"].append(getTravelerInfo(travelerInfo));

        root.append(room);
    }
    outputFile << root << endl;
    return true;
}

vector<RoomInfo> FileHandler::readFromRoomFile(string path)
{
    Json::Value root;
    std::ifstream inputFile(path, std::ifstream::binary);
    vector<RoomInfo> info;
    inputFile >> root;

    for(auto room = root.begin(); room != root.end() ; room++)
    {
        RoomInfo room_info;

        room_info.number = (*room)["number"].asString();
        room_info.status = (*room)["status"].asInt();
        room_info.price = (*room)["price"].asInt();
        room_info.maxCapacity = (*room)["max_capacity"].asInt();
        room_info.capacity = (*room)["capacity"].asInt();
        room_info.room_residents = getTravelers((*room)["room_residents"]);

        info.push_back(room_info);
    }
    return info;
}

Json::Value FileHandler::getTravelerInfo(TravelerInfo traveler)
{
    Json::Value root;
    root["id"] = traveler.id;
    root["number_of_beds"] = traveler.number_of_beds;
    root["checkin_date"] = getDate(traveler.checkin_date);
    root["checkout_date"] = getDate(traveler.checkout_date);
    return root;  
}

Json::Value FileHandler::getDate(Date date)
{
    Json::Value root;
    root["day"] = date.day;
    root["month"] = date.month;
    root["year"] = date.year;
    return root;
}

vector<TravelerInfo> FileHandler::getTravelers(Json::Value root)
{
    vector<TravelerInfo> travelers;
    for(auto traveler = root.begin(); traveler != root.end() ; traveler++)
    {
        TravelerInfo travelerInfo;

        travelerInfo.id = (*traveler)["id"].asInt();
        travelerInfo.number_of_beds = (*traveler)["number_of_beds"].asInt();
        travelerInfo.checkin_date = getDate((*traveler)["checkin_date"]);
        travelerInfo.checkout_date = getDate((*traveler)["checkout_date"]);

        travelers.push_back(travelerInfo);
    }
    return travelers;
}

Date FileHandler::getDate(Json::Value root)
{
    Date date;
    date.day = root["day"].asInt();
    date.month = root["month"].asInt();
    date.year = root["year"].asInt();
    return date;
}
#ifndef __USER_H__
#define __USER_H__
#include "consts.hpp"

class User
{
public:
    User(
        const int& _id,
        const std::string& _username,
        const std::string& _password,
        const bool& _isAdmin,
        const std::string& _purse,
        const std::string& _phoneNumber,
        const std::string& _address,
        const int& _numOfBeds,
        std::string& _reserveDate,
        std::string& _checkoutDate,
        const int& _userRoomNum
    );

private:
    int id;
    std::string username;
    std::string password;
    bool isAdmin;
    std::string purse;
    std::string phoneNumber;
    std::string address;
    int numOfBeds;
    std::string reserveDate;
    std::string checkoutDate;
    int userRoomNum;
};

#endif
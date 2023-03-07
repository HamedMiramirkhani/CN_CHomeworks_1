#ifndef __USER_H__
#define __USER_H__

#include <string>

class User
{
public:
    User(
        const int& id,
        const std::string& user,
        const std::string& password,
        const bool& admin,
        const std::string& purse,
        const std::string& phoneNumber,
        const std::string& address
    );

    int id;
    std::string user;
    std::string password;
    bool admin;
    std::string purse;
    std::string phoneNumber;
    std::string address;
};

#endif
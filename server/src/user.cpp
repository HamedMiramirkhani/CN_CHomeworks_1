#include "user.hpp"

User::User(
        const int& id,
        const std::string& user,
        const std::string& password,
        const bool& admin,
        const std::string& purse,
        const std::string& phoneNumber,
        const std::string& address
    ):
        id(id), 
        user(user), 
        password(password),
        admin(admin),
        purse(purse),
        phoneNumber(phoneNumber),
        address(address) {}
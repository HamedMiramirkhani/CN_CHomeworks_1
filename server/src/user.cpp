#include "user.hpp"

User::User(
        const int& id,
        const std::string& username,
        const std::string& password,
        const bool& isAdmin,
        const std::string& purse,
        const std::string& phoneNumber,
        const std::string& address,
        const int& numOfBeds,
        std::string& reserveDate,
        std::string& checkoutDate,
        const int& userRoomNum
    ):
        id(id),
        username(username), 
        password(password),
        isAdmin(isAdmin),
        purse(purse),
        phoneNumber(phoneNumber),
        address(address),
        numOfBeds(numOfBeds), 
        reserveDate(reserveDate),
        checkoutDate(checkoutDate),
        userRoomNum(userRoomNum) {}

#include "user.hpp"

User::User(
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
    ):
        id(_id),
        username(_username), 
        password(_password),
        isAdmin(_isAdmin),
        purse(_purse),
        phoneNumber(_phoneNumber),
        address(_address),
        numOfBeds(_numOfBeds), 
        reserveDate(_reserveDate),
        checkoutDate(_checkoutDate),
        userRoomNum(_userRoomNum) {}

#ifndef __ROOM_H__
#define __ROOM_H__

#include <string>
#include <vector>
#include <user.hpp>

class Room
{
public:
    Room(
        const std::string& number,
        const bool& status,
        const int& price,
        const int& maxCapacity,
        const int& capacityusers,
        std::vector<User*> room_users
    );

    
    std::string number;
    bool status;
    int price;
    int maxCapacity;
    int capacityusers;
    std::vector<User*> room_users;
};

#endif
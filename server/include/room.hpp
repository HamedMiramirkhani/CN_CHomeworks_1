#ifndef __ROOM_H__
#define __ROOM_H__

#include <string>
#include <vector>
#include <user.hpp>

class Room
{
public:
    Room(
        const int& _number,
        const bool& _status,
        const int& _price,
        const int& _maxCapacity,
        const int& _capacityUsers,
        std::vector<User*> _roomUsers
    );
    int number;
    bool status;
    int price;
    int maxCapacity;
    int capacityUsers;
    std::vector<User*> roomUsers;
};

#endif
#include "room.hpp"

Room::Room(
        const int& _number,
        const bool& _status,
        const int& _price,
        const int& _maxCapacity,
        const int& _capacityUsers,
        std::vector<User*> _roomUsers
    ): 
        number(_number), 
        status(_status), 
        price(_price),
        maxCapacity(_maxCapacity),
        capacityUsers(_capacityUsers),
        roomUsers(_roomUsers) {}

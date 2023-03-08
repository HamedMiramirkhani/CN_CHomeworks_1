#include "room.hpp"

Room::Room(
        const int& number,
        const bool& status,
        const int& price,
        const int& maxCapacity,
        const int& capacityusers,
        std::vector<User*> room_users
    ): 
        number(number), 
        status(status), 
        price(price),
        maxCapacity(maxCapacity),
        capacityusers(capacityusers),
        room_users(room_users) {}

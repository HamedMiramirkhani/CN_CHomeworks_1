#ifndef __DASHBOARD_HPP__
#define __DASHBOARD_HPP__

#include <vector>
// 
#include "menuList.hpp"
#include "classNames.hpp"

class Dashboard
{
public:
    Dashboard(/* args */);
    //
    //
    // sth
private:
    std::vector<Person*> allUsers;
    std::vector<Room*> allRooms;
    std::unordered_map<int, Person*> usersFdMap;
    std::string line;
    int userFd;
    int lastId;
};

#endif

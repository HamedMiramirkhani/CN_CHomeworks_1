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

    char* getResponse(int clientFd, char* request);

    
    bool connectionClosed(int clientFd);
    void addNewClient(int clientFd);
    void handleCommand(int fd, std::string command);
    std::unordered_map<std::string, func_ptr> getCmdList(int fd);
    // must add these to dashboard.cpp:
    void signup();
    void signin();
    void viewUserInfo();
    void viewAllUsers();
    void viewRoomsInformationForUser();
    void viewRoomsInformationForAdmin();

private:
    std::vector<Person*> allUsers;
    std::vector<Room*> allRooms;
    std::unordered_map<int, Person*> usersFdMap;
    std::string line;
    int userFd;
    int lastId;
    DateConfig* today;
};

#endif

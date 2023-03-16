#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <memory>

#include "classNames.hpp"

class Dashboard
{
public:
    Dashboard(/* args */);

    char* getResponse(int client_fd, char* request);

    /// IMPORTATNT: some other client may use this same fd in future and it must be handled 
    bool connection_closed(int closed_client_fd);
    void addNewClient(int new_client_fd);
    void handle_command(int fd, std::string command);
    std::unordered_map<std::string, func_ptr> getCmdList(int fd);
    void route_command(std::string cmd, const std::unordered_map<std::string, func_ptr> &list);
    void signup();
    void signin();
    void viewUserInformation();
    void viewAllUsers();
    void viewRoomsInfoForUser();
    void viewRoomsInfoForAdmin();
    void book();
    void showReservations();
    void cancel();
    void passDay();
    void editInfoForUser();
    void editInfoForAdmin();
    void leavingRoomForUser();
    void leavingRoomForAdmin();
    void rooms();
    void logout();
    void checkExistUsername(std::string username);
    void findSignedInUser(std::string username, std::string password);
    void getRoomsInfo(bool isAdmin, int filter_empty_status);
    void bookOptions(int RoomNum,int NumOfBeds, std::string CheckInDate, std::string CheckOutDate);
    void updateRooms();
    void roomsAdd();
    void roomsChange();
    void roomsRemove();
    void checkExistRoom(std::string RoomNum);
    int  findRoom(int room_num);
    void checkRoomEmpty(int room_index);
private:
    std::vector<Person*> allUsers;
    std::vector<std::shared_ptr<Room>> allRooms;
    std::unordered_map<int, Person*> usersFdMap;
    std::string line;
    int userFd;
    int lastID;
    DateConfig* today;
};

const std::unordered_map<std::string, func_ptr> unregisteredUserList = {
    {"signup", &Dashboard::signup},
    {"signin", &Dashboard::signin},
};

const std::unordered_map<std::string, func_ptr> userCmdList = {
    {"viewUserInformation", &Dashboard::viewUserInformation},
    {"view_rooms_information", &Dashboard::viewRoomsInfoForUser},
    {"book", &Dashboard::book},
    {"showReservations", &Dashboard::showReservations},
    {"cancel", &Dashboard::cancel},
    {"edit_information", &Dashboard::editInfoForUser},
    {"leaving_room", &Dashboard::leavingRoomForUser},
    {"logout", &Dashboard::logout},
};

const std::unordered_map<std::string, func_ptr> adminCmdList = {
    {"viewUserInformation", &Dashboard::viewUserInformation},
    {"viewAllUsers", &Dashboard::viewAllUsers},
    {"view_rooms_information", &Dashboard::viewRoomsInfoForAdmin},
    {"passDay", &Dashboard::passDay},
    {"edit_information", &Dashboard::editInfoForAdmin},
    {"leaving_room", &Dashboard::leavingRoomForAdmin},
    {"rooms", &Dashboard::rooms},
    {"logout", &Dashboard::logout},
};

const std::unordered_map<std::string, func_ptr> roomsCmdList = {
    {"add", &Dashboard::roomsAdd},
    {"modify", &Dashboard::roomsChange},
    {"remove", &Dashboard::roomsRemove},
};
// #ifndef __CMD_HANDLER_H__
// #define __CMD_HANDLER_H__
// #include "consts.hpp"

// const int ERROR = -1;

// class CmdHandler
// {
// public:
//     CmdHandler();
//     void runCommand(int fd, char* readBuffer);

// private:
//     std::vector<std::string> splitString(const std::string& s, char delimiter);

//     void signin(int fd, std::vector<std::string> splittedBuffer);

//     class FdID
//     {
//     public:
//         FdID(void);
//         bool add(int fd, int id);
//         int get(int fd);
//         bool remove(int fd);
    
//     private:
//         std::map<int, int> mapFdID;
//     };

// };

// #endif

#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__
#include "consts.hpp"
#include "user.hpp"
#include "room.hpp"
#include "logger.hpp"

class CmdHandler
{
public:
    CmdHandler(std::vector<User*> allUsers,
     std::vector<Room*> allRooms);
    std::string runCommand(std::string input);
    std::vector<std::string> splitString
    (const std::string& s, char delimiter); 
    //handle different commands


private:
    std::vector<std::string> 
    splitString(const std::string& s, char delimiter);

    std::vector<User*> users;
    std::vector<Room*> allRooms
    Logger cmdHndlrLogger;
    
    User* current_user;
    bool logged_in;
    bool logging_in;
    User* logging_in_user;
    bool is_admin;
    std::string current_directory;
};

#endif
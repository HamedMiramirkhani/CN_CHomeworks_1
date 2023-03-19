#pragma once
//libs
#include <stdio.h>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdbool.h>
//colors
#define RED_COLOR "\x1B[31m"
#define WHITE_COLOR "\x1B[37m"
//consts
#define MAX_STRING_SIZE 4096
#define PRINT_INIT_CMD write(STD_OUT, ">>" , strlen(">>"))

typedef std::vector<std::string> str_list;

const std::string CONFIG_SERVER_DATA_PATH = "./../json_files/config.json";

struct Config
{
    std::string hostName;
    int commandChannelPort;
};

enum io_type {STD_IN = 0, STD_OUT = 1};

enum commands_nums
{
    logout_cmdNum = 0,
    //startCommand
    signup_cmdNum = 1,
    signin_cmdNum = 2,
    //ReserveCommand
    View_user_information_cmdNum = 3,
    View_all_users_cmdNum = 4,
    View_rooms_information_cmdNum = 5,
    Booking_cmdNum = 6,
    Canceling_cmdNum = 7,
    pass_day_cmdNum = 8,
    Edit_information_cmdNum = 9,
    Leaving_room_cmdNum = 10,
    //RoomCommand
    Rooms_cmdNum = 11,
    Rooms_add_cmdNum = 12,
    Rooms_modify_cmdNum = 13,
    Rooms_remove_cmdNum = 14
};

enum commands_mode
{
    not_registered_menu = 1,
    registered_menu = 2,
};

enum options_mode
{
    options_not_required = 1,
    options_required = 2,
};

struct commands_names
{
    static std::map<int,std::string> create_map()
    {
        std::map<int,std::string> names = 
        {
            {signup_cmdNum, "signup"},
            {signin_cmdNum, "signin"},
            {logout_cmdNum, "logout"},
            {View_user_information_cmdNum, "view_user_information"},
            {View_all_users_cmdNum, "view_all_users"},
            {View_rooms_information_cmdNum, "view_rooms_information"},
            {Booking_cmdNum, "book"},
            {Canceling_cmdNum, "cancel"},
            {pass_day_cmdNum, "pass_day"},
            {Edit_information_cmdNum, "edit_information"},
            {Leaving_room_cmdNum, "leaving_room"},
            {Rooms_cmdNum, "rooms"},
            {Rooms_add_cmdNum, "rooms"},
            {Rooms_add_cmdNum, "rooms"},
            {Rooms_add_cmdNum, "rooms"},
        };
        return names;
    }
    static std::map<int,std::string> desired_map;
};

struct commands_help
{
    static std::map<int,std::string> create_map()
    {
        std::map<int,std::string> messages = 
        {
            {logout_cmdNum, ""},
            {signup_cmdNum, "Err -> 311: User Signed up. Enter your username, password, purse, \
            phone and address.\nCommand -> <username> <password> <purse> <phone> <address>\n"},
            {signin_cmdNum, "Command -> <username> <password>\n\nHelp -> username: \
            Username, password: user password\n"},
            {View_user_information_cmdNum, ""},
            {View_all_users_cmdNum, ""},
            {View_rooms_information_cmdNum, "Command -> filter_empty <empty filter>\n\nHelp -> \
            empty filter: type enable or enter (for admin this is not matter)\n"},
            {Booking_cmdNum, "Command -> <RoomNum> <NumOfBeds> <CheckInDate> <CheckOutDate>\n\n \
            Help -> RoomNum: Number of room, NumOfBeds: Number of reservation(per person)\nHelp -> \
            CheckInDate: Start date of reservation, CheckOutDate: End date of reservation\n"},
            {Canceling_cmdNum, "Command -> <RoomNum> <Num>\n\nHelp -> RoomNum: Number of room, Num: \
            Number of reservation(per person)\n"},
            {pass_day_cmdNum, "Command -> <value>\n\nHelp -> value: number of day you want to pass\n"},
            {Edit_information_cmdNum, "Command -> new_password <new password> phone <phone> address \
            <address>\n\nNote: all flags are optional\n"},
            {Leaving_room_cmdNum, "for user :\nCommand -> value <value>\nfor admin:\nCommand -> value \
            <value> new_capacity <new capacity>\n\nHelp -> value: Room number\nHelp -> \
            new capacity: Enter new capacity of the room\n"},
            {Rooms_cmdNum, "Command -> add <RoomNum> <Max Capacity> <Price>\nCommand \
            -> modify RoomNum <RoomNum> Max_Capacity <new Max Capacity> Price \
            <new Price>\nCommand -> remove <RoomNum>\n"},
        };
        return messages;
    }
    static std::map<int,std::string> desired_map;
};

struct commands_list
{
    static std::map<int,std::string> create_map()
    {
        std::map<int,std::string> messages = 
        {
            {not_registered_menu, "1. signup\n2. signin\nCommand -> <Choice number>\n\n"},
            {registered_menu, "3. View_user_information\n4. View_all_users\n5. View_rooms_information\n6. Booking\n7. Canceling\n8. pass_day\n9. Edit_information\n10. Leaving_room\n11. Rooms\n0. logout\n\n"},
        };
        return messages;
    }
    static std::map<int,std::string> desired_map;
};

struct commands_with_options
{
    static std::map<int, std::pair<int, str_list>> create_map()
    {
        std::map<int, std::pair<int, str_list>> options = 
        {
            {signup_cmdNum, {options_required, {"username", "password", "purse", "phone", "address"}}},
            {signin_cmdNum, {options_required, {"username", "password"}}},
            {logout_cmdNum, {options_required, {}}},
            {View_user_information_cmdNum, {options_required, {}}},
            {View_all_users_cmdNum, {options_required, {}}},
            {View_rooms_information_cmdNum, {options_not_required, {"filter_empty"}}},
            {Booking_cmdNum, {options_required, {"RoomNum", "NumOfBeds", "CheckInDate", "CheckOutDate"}}},
            {Canceling_cmdNum, {options_required, {"RoomNum", "Num"}}},
            {pass_day_cmdNum, {options_required, {"value"}}},
            {Edit_information_cmdNum, {options_not_required, {"new_password", "phone", "address"}}},
            {Leaving_room_cmdNum, {options_not_required, {"value", "new_capacity"}}},
            {Rooms_cmdNum, {options_required, {}}},
            {Rooms_add_cmdNum, {options_required, {"room_command_request", "RoomNum", "Max_Capacity", "Price"}}},
            {Rooms_modify_cmdNum, {options_not_required, {"room_command_request", "RoomNum", "Max_Capacity", "Price"}}},
            {Rooms_remove_cmdNum, {options_required, {"room_command_request", "RoomNum"}}},
        };
        return options;
    }
    static std::map<int, std::pair<int, str_list>> desired_map;
};

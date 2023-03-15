#pragma once

#include <string>
#include <unordered_map>
#include "classNames.hpp"

const std::unordered_map<std::string, funcPtr> unregistered_user_list = {
    {"signup", &Dashboard::signup},
    {"signin", &Dashboard::signin},
};

const std::unordered_map<std::string, funcPtr> user_command_list = {
    {"view_user_information", &Dashboard::view_user_information},
    {"view_rooms_information", &Dashboard::view_rooms_information_for_user},
    {"booking", &Dashboard::booking},
    {"canceling", &Dashboard::canceling},
    {"edit_information", &Dashboard::edit_information_for_user},
    {"leaving_room", &Dashboard::leaving_room_for_user},
    {"logout", &Dashboard::logout},
};

const std::unordered_map<std::string, funcPtr> admin_command_list = {
    {"view_user_information", &Dashboard::view_user_information},
    {"view_all_users", &Dashboard::view_all_users},
    {"view_rooms_information", &Dashboard::view_rooms_information_for_admin},
    {"pass_day", &Dashboard::pass_day},
    {"edit_information", &Dashboard::edit_information_for_admin},
    {"leaving_room", &Dashboard::leaving_room_for_admin},
    {"rooms", &Dashboard::rooms},
    {"logout", &Dashboard::logout},
};

const std::unordered_map<std::string, funcPtr> rooms_command_list = {
    {"add", &Dashboard::rooms_add},
    {"modify", &Dashboard::rooms_modify},
    {"remove", &Dashboard::rooms_remove},
};
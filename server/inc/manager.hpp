#pragma once

#include "help.hpp"
#include "error.hpp"
#include "person.hpp"
#include "room.hpp"

class Manager
{
public:
    Manager(/* args */);

    void set_today(std::string server_input);
    void add_new_client(int new_client_fd);
    std::string handle_command(int fd, std::string command);
    std::unordered_map<std::string, func_ptr> get_command_list(int fd);
    void signup();
    void signin();
    void view_user_information();
    void view_all_users();
    void view_rooms_info_for_user();
    void view_rooms_info_for_admin();
    void book();
    void show_reservations();
    void cancel();
    void pass_day();
    void edit_information_for_user();
    void edit_information_for_admin();
    void leaving_room_for_user();
    void leaving_room_for_admin();
    void rooms();
    std::string get_rooms_info(bool is_admin, int filter_empty_status);
    void rooms_add();
    void rooms_modify();
    void rooms_remove();
    int  find_room(int room_num);
    int  chaeck_filter();
    void save_data();
    void logout();
private:
    std::vector<FileDataContainers::RentInfo> get_rents(Json::Value users);
    std::vector<FileDataContainers::RoomInfo> read_rooms_info();
    std::vector<FileDataContainers::UserInfo> read_users_info();
    void write_users_info(std::vector<FileDataContainers::UserInfo> info);
    void write_rooms_info(std::vector<FileDataContainers::RoomInfo> info);

    std::string split_line_by_space(std::string str);
    DateConfig convert_to_DataConfig(std::string str);
    void load_data();

    std::vector<Person*> all_users;
    std::vector<std::shared_ptr<Room>> all_rooms;
    std::unordered_map<int, Person*> users_fd_map;
    std::string line;
    int user_fd;
    int last_id;
    DateConfig* today;
};

const std::unordered_map<std::string, func_ptr> unregistered_user_list = {
    {"signup", &Manager::signup},
    {"signin", &Manager::signin},
};

const std::unordered_map<std::string, func_ptr> user_command_list = {
    {"view_user_information", &Manager::view_user_information},
    {"view_rooms_information", &Manager::view_rooms_info_for_user},
    {"book", &Manager::book},
    {"show_reservations", &Manager::show_reservations},
    {"cancel", &Manager::cancel},
    {"edit_information", &Manager::edit_information_for_user},
    {"leaving_room", &Manager::leaving_room_for_user},
    {"logout", &Manager::logout},
};

const std::unordered_map<std::string, func_ptr> admin_command_list = {
    {"view_user_information", &Manager::view_user_information},
    {"view_all_users", &Manager::view_all_users},
    {"view_rooms_information", &Manager::view_rooms_info_for_admin},
    {"pass_day", &Manager::pass_day},
    {"edit_information", &Manager::edit_information_for_admin},
    {"leaving_room", &Manager::leaving_room_for_admin},
    {"rooms", &Manager::rooms},
    {"logout", &Manager::logout},
};

const std::unordered_map<std::string, func_ptr> rooms_command_list = {
    {"add", &Manager::rooms_add},
    {"modify", &Manager::rooms_modify},
    {"remove", &Manager::rooms_remove},
};
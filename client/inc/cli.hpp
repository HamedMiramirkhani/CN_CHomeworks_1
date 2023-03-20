#pragma once

#include "helpCli.hpp"

class Cli
{
public:
    Cli();
    void need_show_menu(std::string response);
    void set_server_fd(const int server_fd);
    void handle_commad(std::string message);
    void print_help(std::string help_message);
    std::string get_input(bool need_print_init=true);
    void clear();
private:
    int update_mode(std::string response, int menu_mode);
    void check_cancling();
    void check_room_commands(int& command_num, std::string& options_line);
    std::string make_msg(std::vector<std::string> options, std::string options_line, int option_mode);
    std::vector<std::string> make_list_from_line(std::string line, char divider);
    std::string parse_line(std::string str, char del);
    std::string get_param(std::string line, std::string key, bool required);
    int server_fd_cli;
    int menu_mode;
};
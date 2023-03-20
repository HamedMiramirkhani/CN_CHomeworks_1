#include "errorCMD.hpp"
#include "cli.hpp"
#include "helpCli.hpp"

using namespace std;

map<int, string> commands_help::desired_map = commands_help::create_map();
map<int, string> commands_list::desired_map = commands_list::create_map();
map<int, string> commands_names::desired_map = commands_names::create_map();
map<int, pair<int, vector<string>>> commands_with_options::desired_map = commands_with_options::create_map();

Cli::Cli()
{ menu_mode = not_registered_menu; }

string Cli::get_input(bool need_print_init)
{
    if(need_print_init)
        PRINT_INIT_CMD;

    char cmd[MAX_STRING_SIZE] = {0};
    int last_char = read(STD_IN, cmd, MAX_STRING_SIZE);
    cmd[last_char - 1] = '\0';

    string msg = cmd;
    return msg;
}

void Cli::set_server_fd(const int server_fd)
{server_fd_cli = server_fd;}

int Cli::update_mode(std::string response, int menu_mode)
{
    if(response.find("USER_LOGED_OUT_SUCCESSFULLY") != std::string::npos)
        return not_registered_menu;
    else if(response.find("USER_LOGED_IN") != std::string::npos)
        return registered_menu;
    else
        return menu_mode;
}

void Cli::need_show_menu(std::string response)
{
    int old_mode = menu_mode;
    menu_mode = update_mode(response, menu_mode);
    if(old_mode != menu_mode)
        cout << commands_list::desired_map[menu_mode];
}

void Cli::handle_commad(string msg)
{
    if(msg.find("cls") != std::string::npos) 
    {
        clear();
        return;
    }

    if(!all_of(msg.begin(), msg.end(), ::isdigit)) //is cmd num?
        throw ErrorCMD("Enter number!\n");

    int command_num = stoi(msg);
    if(command_num == Canceling_cmdNum && menu_mode == registered_menu)
        check_cancling();
    
    string options_line = "";
    if(command_num == Rooms_cmdNum)
        check_room_commands(command_num, options_line);

    auto command_options = commands_with_options::desired_map[command_num];
    
    if(command_options.first == 0) //find cmd?
        throw ErrorCMD("Enter correct number!\n");

    string options = "";
    if(!command_options.second.empty())
    {
        if(options_line == "" && !command_options.second.empty()) 
            print_help(commands_help::desired_map[command_num]);

        options = make_msg(command_options.second, 
        options_line, command_options.first);
    }
    string formated_command = commands_names::desired_map[command_num] + " " + options;
    send(server_fd_cli, formated_command.c_str(), strlen(formated_command.c_str()), 0);
}

void Cli::check_cancling()
{
    string list_reservations_command = "show_reservations";
    send(server_fd_cli, list_reservations_command.c_str(), 
    strlen(list_reservations_command.c_str()), 0);    
}

void Cli::check_room_commands(int& command_num, string& options_line)
{
    print_help(commands_help::desired_map[Rooms_cmdNum]);
    options_line = get_input();
    string first_part_of_command = parse_line(options_line, ' ');
    command_num = (first_part_of_command == "add") ? Rooms_add_cmdNum :
                  (first_part_of_command == "modify") ? Rooms_modify_cmdNum :
                  (first_part_of_command == "remove") ? Rooms_remove_cmdNum :
                   command_num;
    if(first_part_of_command == "modify")
        options_line = "room_command_request " + options_line;
}

void Cli::print_help(std::string help_message)
{ cout << endl << "HELP:" << endl << help_message << endl;}

vector<string> Cli::make_list_from_line(string line, char divider) 
{
    string argument;
    istringstream arguments(line);
    vector<string> dividedLine;
    while (getline(arguments, argument, divider)) 
    {
        if (argument == "")
            continue;
        dividedLine.push_back(argument);
    }
    return dividedLine;
}

string Cli::parse_line(string str, char del) 
{
    str.append(" ");
    string res = "";
    istringstream sstream(str);
    getline(sstream, res, del);
    str = str.substr(res.size() + 1);
    return res;
}

string Cli::get_param(string line, string key, bool required) 
{
    vector<string> words = make_list_from_line(line, ' ');
    auto it = find(words.begin(), words.end(), key);
    if (it == words.end())
    {
        if (required)
            throw ErrorCMD("Enter right options!\n");
        else
            return "";
    }
    auto index = distance(words.begin(), it);
    return words[index + 1];
}

string Cli::make_msg(vector<string> options, string options_line, int option_mode)
{
    string input_options = (options_line == "") ? get_input() : options_line;
    ostringstream info;
    if(option_mode == options_required) {
        auto input_options_ = make_list_from_line(input_options, ' ');
        if(input_options_.size() != options.size())
            throw ErrorCMD("Enter right options!\n");

        for (unsigned int i = 0; i < options.size(); i++)
            info << options[i] << " " << input_options_[i] << " ";
    }
    else {
        string param;
        for (auto option : options) {
            param = get_param(input_options, option, false);
            if(param != "")
                info << option << " " << param << " ";
        }
    }
    return info.str();   
}

void Cli::clear()
{
    system("clear");
    cout << commands_list::desired_map[menu_mode];
    PRINT_INIT_CMD;
}
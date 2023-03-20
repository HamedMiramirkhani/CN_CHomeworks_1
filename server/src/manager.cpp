#include "manager.hpp"

using namespace std;

Manager::Manager(/* args */)
{
    last_id = 0;
    load_data();
}

string Manager::split_line_by_space(string str) 
{
    str.append(" ");
    string res = "";
    istringstream sstream(str);
    getline(sstream, res, ' ');
    str = str.substr(res.size() + 1);
    return res;
}

string get_param_manager(string line, string key, bool required=true) 
{
    string ever_word;
    istringstream all_words(line);
    vector<string> words;
    while (getline(all_words, ever_word, ' ')) {
        if (ever_word == "")
            continue;
        words.push_back(ever_word);
    }

    auto it = find(words.begin(), words.end(), key);
    if (it == words.end())
    {
        if (required)
            throw Error(503);
        else
            return "";
    }
    return words[distance(words.begin(), it) + 1];
}

void Manager::set_today(string server_input)
{
    DateConfig date_config = 
    convert_to_DataConfig(get_param_manager(server_input, "setTime"));

    today = new DateConfig(date_config.day, date_config.month, date_config.year);

    for(int i=0; i < all_rooms.size(); i++)
        all_rooms[i]->update_room(today);

    printf("time is set.\n");
}

void Manager::add_new_client(const int new_client_fd)
{
    printf("\tNew costumer connected.fd=%d\n", new_client_fd);
    send(new_client_fd, "\tWelcome!\n1. signup\n2. signin\nCommand -> <Choice number>\n",
     strlen("Welcome!\n1. signup\n2. signin\nCommand -> <Choice number>\n"), 0);
    users_fd_map[new_client_fd] = nullptr;
}

DateConfig Manager::convert_to_DataConfig(string str)
{
    str.push_back('-');
    istringstream arguments(str);
    string day, month, year;
    getline(arguments, day, '-');
    getline(arguments, month, '-');
    getline(arguments, year, '-');

    return DateConfig(stoi(day), stoi(month), stoi(year));
}

string Manager::handle_command(const int fd, string command)
{
    line = command;
    user_fd = fd;
    string cmd = split_line_by_space(command);
    try {
        auto list = get_command_list(user_fd);
        auto func = list.find(cmd);
        if (func == list.end()) 
            throw Error(403);
        (this->*(func->second))();
    } 
    catch (Error& error) {
        save_data();
        return error.what();
    } 
    catch (Message& message) {
        save_data();
        return message.what();
    }
    return "";
}

unordered_map<string, func_ptr> Manager::get_command_list(int fd)
{
    Person* person = users_fd_map[fd];
    if(person == nullptr)
        return unregistered_user_list;
    else
        return person->get_command_list();
}

vector<FileDataContainers::UserInfo> Manager::read_users_info()
{
    ifstream input_file(Paths::USERS_DATA_PATH, ifstream::binary);
    Json::Value root;
    input_file >> root;

    vector<FileDataContainers::UserInfo> info;
    for(auto user = root.begin(); user != root.end() ; user++)
    {
        FileDataContainers::UserInfo new_user;
        new_user.id = (*user)["id"].asInt();
        new_user.user = (*user)["user"].asString();
        new_user.password = (*user)["password"].asString();
        new_user.admin = (*user)["admin"].asBool();
        if(!new_user.admin) {
            new_user.purse = (*user)["purse"].asInt();
            new_user.phoneNumber = (*user)["phoneNumber"].asString();
            new_user.address = (*user)["address"].asString();
        }
        info.push_back(new_user);
    }
    return info;
}

vector<FileDataContainers::RentInfo> Manager::get_rents(Json::Value users)
{
    vector<FileDataContainers::RentInfo> info;
    for(auto rent = users.begin(); rent != users.end() ; rent++)
    {
        FileDataContainers::RentInfo rent_info;
        rent_info.id = (*rent)["id"].asInt();
        rent_info.numOfBeds = (*rent)["numOfBeds"].asInt();
        rent_info.reserveDate = (*rent)["reserveDate"].asString();
        rent_info.checkoutDate = (*rent)["checkoutDate"].asString();
        info.push_back(rent_info);
    }
    return info;
}

vector<FileDataContainers::RoomInfo> Manager::read_rooms_info()
{
    ifstream input_file(Paths::ROOMS_DATA_PATH, ifstream::binary);
    Json::Value root;
    input_file >> root;

    vector<FileDataContainers::RoomInfo> info;
    for(auto user = root.begin(); user != root.end() ; user++)
    {
        FileDataContainers::RoomInfo room_info;
        room_info.number = (*user)["number"].asInt();
        room_info.status = (*user)["status"].asInt();
        room_info.price = (*user)["price"].asInt();
        room_info.maxCapacity = (*user)["maxCapacity"].asInt();
        room_info.capacity = (*user)["capacity"].asInt();
        room_info.users = get_rents((*user)["users"]);
        info.push_back(room_info);
    }
    return info;
}

void Manager::write_users_info(vector<FileDataContainers::UserInfo> info)
{
    Json::Value root;
    ofstream output_file(Paths::USERS_DATA_PATH, ifstream::binary);
    for(auto user_info : info)
    {
        Json::Value user; 
        user["id"] = user_info.id;
        user["user"] = user_info.user;
        user["password"] = user_info.password;
        user["admin"] = user_info.admin;
        if(!user_info.admin)
        {
            user["purse"] = user_info.purse;
            user["phoneNumber"] = user_info.phoneNumber;
            user["address"] = user_info.address;
        }
        root.append(user);
    }
    output_file << root << endl;
}

void Manager::write_rooms_info(vector<FileDataContainers::RoomInfo> info)
{
    Json::Value root;
    ofstream output_file(Paths::ROOMS_DATA_PATH, ifstream::binary);
    for(auto room_info : info)
    {
        Json::Value room; 
        room["number"] = room_info.number;
        room["status"] = room_info.status;
        room["price"] = room_info.price;
        room["maxCapacity"] = room_info.maxCapacity;
        room["capacity"] = room_info.capacity;
        for(auto rent : room_info.users)
        {
            Json::Value new_user;
            new_user["id"] = rent.id;
            new_user["numOfBeds"] = rent.numOfBeds;
            new_user["reserveDate"] = rent.reserveDate;
            new_user["checkoutDate"] = rent.checkoutDate;
            room["users"].append(new_user);
        }
        root.append(room);
    }
    output_file << root << endl;
}

void Manager::load_data()
{
    //users
    auto users_buffer = read_users_info();
    for(auto user : users_buffer)
        if(user.admin)
            all_users.push_back(new Admin(user.id, user.user, user.password));
        else
            all_users.push_back(new User(user.id, user.user, user.password, user.purse, user.phoneNumber, user.address));
    //rooms
    auto rooms_buffer = read_rooms_info();
    for(auto room : rooms_buffer)
    {
        vector<shared_ptr<Rent>> rents;
        for(auto rent : room.users)
        {
            Person* user;
            for(auto user_ : all_users)
                if(user_->has_this_id(rent.id))
                    user = user_;
            rents.push_back(make_shared<Rent>(user, rent.numOfBeds, 
                                              convert_to_DataConfig(rent.reserveDate),
                                              convert_to_DataConfig(rent.checkoutDate)));
        }
        all_rooms.push_back(make_shared<Room>(room.number, room.status, room.price, 
                                              room.maxCapacity, room.capacity, rents));
    }
}

void Manager::save_data()
{
    //users
    vector<FileDataContainers::UserInfo> info;
    for(auto user : all_users)
        info.push_back(user->get_data_for_write());
    write_users_info(info);
    //rooms
    vector<FileDataContainers::RoomInfo> sec_info;
    for(auto room : all_rooms)
        sec_info.push_back(room->get_data_for_write());
    write_rooms_info(sec_info);
}
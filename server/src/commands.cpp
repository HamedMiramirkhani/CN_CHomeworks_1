#include "manager.hpp"
#include "help.hpp"
#include "error.hpp"

using namespace std;

string get_param(string line, string key, bool required=true, bool must_print = false) 
{
    if(must_print)
        cout << key;
    vector<string> words;
    string ever_word;
    istringstream all_words(line);
    while (getline(all_words, ever_word, ' ')) {
        if (ever_word == "")
            continue;
        words.push_back(ever_word);
    }

    auto x = find(words.begin(), words.end(), key);
    if (x == words.end())
    {
        if (required)
            throw Error(503);
        else
            return "";
    }
    return words[distance(words.begin(), x) + 1];
}

void Manager::signup()
{
    string username = get_param(line, "username"),
    password = get_param(line, "password"),
    purse = get_param(line, "purse"),
    phone = get_param(line, "phone"),
    address = get_param(line, "address");
    
    for(auto person : all_users) //exist_username?
        if (person->has_this_username(username))
            throw Error(451);

    all_users.push_back(new User(last_id++, username, password, stoi(purse), phone, address));
    throw Error(231);
}

void Manager::signin()
{
    string username = get_param(line, "username"),
    password = get_param(line, "password");

    bool found = false;
    for(auto person : all_users) {
        if (person->check_info(username, password)) {
            users_fd_map[user_fd] = person;
            found = true;
        }
    }

    if(!found)
        throw Error(430);
    else
        throw Error(230);
}

void Manager::view_all_users()
{
    ostringstream info;
    for(int i=0; i < all_users.size(); i++)
        info << all_users[i]->get_info(" , ");

    throw Message(info.str());
}

void Manager::view_user_information()
{ throw Message(users_fd_map[user_fd]->get_info("\n")); }

int Manager::chaeck_filter() 
{
    int filter_status = DISABLE;
    if(get_param(line, "filter_empty", false,  false) != "")
        filter_status = ENABLE;
    
    return filter_status;
}

void Manager::view_rooms_info_for_user()
{ throw Message(get_rooms_info(false, chaeck_filter())); }

void Manager::view_rooms_info_for_admin()
{ throw Message(get_rooms_info(true, DISABLE)); }

string Manager::get_rooms_info(bool is_admin, int filter_status)
{
    ostringstream info;
    for(int i=0; i < all_rooms.size(); i++)
        info << all_rooms[i]->get_info(today, is_admin, filter_status);

    return info.str();
}

void Manager::book()
{
    string room_num = get_param(line, "RoomNum"),
    num_of_beds = get_param(line, "NumOfBeds"),
    check_in_date = get_param(line, "CheckInDate"),
    check_out_date = get_param(line, "CheckOutDate");

    int target_index = find_room(stoi(room_num));
    all_rooms[target_index]->add_new_rent(stoi(num_of_beds),
     check_in_date, check_out_date, users_fd_map[user_fd], today);
    all_rooms[target_index]->update_room(today);

    throw Error(110);
}

void Manager::show_reservations()
{
    ostringstream reserve_list;
    reserve_list << "today: " << today->day << '-' << today->month << '-' << today->year << endl
         << "your money: " << users_fd_map[user_fd]->get_wallet() << endl
         << "your_reservations:" << endl;
    for(int i=0; i < all_rooms.size(); i++)
        reserve_list << all_rooms[i]->get_info_if_reserve(users_fd_map[user_fd]->get_id());
    reserve_list << endl;

    throw Message(reserve_list.str());
}

void Manager::cancel()
{
    int room_num = stoi(get_param(line, "RoomNum")),
    num = stoi(get_param(line, "Num")),
    target_index = find_room(room_num), 
    id = users_fd_map[user_fd]->get_id();

    all_rooms[target_index]->cancel_book(id, num, today);
    throw Error(106);
}

void Manager::pass_day()
{
    string value = get_param(line, "value");
    today->pass_day(value);
    for(int i=0; i < all_rooms.size(); i++)
        all_rooms[i]->update_room(today);

    throw Error(110);
}

void Manager::edit_information_for_user()
{
    string new_password = get_param(line, "new_password", false, false),
    phone = get_param(line, "phone", false, false),
    address = get_param(line, "address", false, false);
    users_fd_map[user_fd]->change_info(new_password, phone, address);

    throw Error(312);
}

void Manager::edit_information_for_admin()
{
    string new_password;
    new_password = get_param(line, "new_password", false, false);
    users_fd_map[user_fd]->change_info(new_password);

    throw Error(312);
}

void Manager::leaving_room_for_user()
{
    int value = stoi(get_param(line, "value"));
    all_rooms[find_room(value)]->leave_room(users_fd_map[user_fd]->get_id(), today);
    throw Error(413);
}

void Manager::leaving_room_for_admin()
{
    int value = stoi(get_param(line, "value")),
    new_capacity = stoi(get_param(line, "new_capacity"));
    all_rooms[find_room(value)]->eject(new_capacity, today);
    all_rooms[find_room(value)]->update_room(today);

    throw Error(110);
}

void Manager::rooms()
{
    string req_room = get_param(line, 
    "room_command_request", false, false);
    auto func = rooms_command_list.find(req_room);
    if (func == rooms_command_list.end()) 
        throw Error(403);
    (this->*(func->second))();
}

void Manager::rooms_add()
{
    int room_num = stoi(get_param(line, "RoomNum")),
    max_capacity = stoi(get_param(line, "Max_Capacity")),
    price = stoi(get_param(line, "Price"));
    //exist room?
    for(int i=0; i < all_rooms.size(); i++)
        if(all_rooms[i]->match_room_num(room_num))
            throw Error(111);

    all_rooms.push_back(make_shared<Room>(room_num,
     EMPTY, price, max_capacity,
     max_capacity, vector<shared_ptr<Rent>>{}));

    throw Error(104);
}

void Manager::rooms_modify()
{
    int room_num = stoi(get_param(line, "RoomNum", false, false));
    string new_Max_Capacity = get_param(line, "Max_Capacity", false, false),
    new_price = get_param(line, "Price", false);
    all_rooms[find_room(room_num)]->change_info(new_Max_Capacity, new_price);

    throw Error(105);
}

void Manager::rooms_remove()
{
    int room_num = stoi(get_param(line, "RoomNum"));
    int room_index = find_room(room_num);
    // is empty room?
    if(all_rooms[room_index]->has_user(today))
        throw Error(109);
        
    all_rooms.erase(all_rooms.begin() + room_index);

    throw Error(106);
}

int Manager::find_room(int room_num)
{
    for(int i = 0; i < all_rooms.size(); i++)
        if(all_rooms[i]->match_room_num(room_num))
            return i;
            
    throw Error(101);
}

void Manager::logout()
{
    users_fd_map[user_fd] = nullptr;
    throw Error(201);
}
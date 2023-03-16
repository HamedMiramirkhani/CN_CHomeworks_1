#include <algorithm>

#include "person.hpp"
#include "dashboard.hpp"
#include "error.hpp"
#include "Utils.hpp"

using namespace std;

Person::Person(int id_,string username_, string password_)
    :
    id(id_),
    username(username_),
    password(password_)
{
}

bool Person::checkInfo(string username_, string password_) 
{
    return (username == username_ && password == password_);
}

bool Person::hasUsername(string username_)
{
    return username_ == username; 
}

bool Person::hasID(int id_)
{
    return id == id_;
}

void Person::changeInfo(string newPassword, string newPhone, string newAddress) {}
void Person::changeInfo(string newPassword) {}
int Person::getPurse() { return 0; }
void Person::checkout(int price) {}
void Person::earn(int price) {}

int Person::getID()
{
    return id;
}

User::User(int id_,string username_, string password_, int purse_, string phoneNumber_, string address_) 
    : 
    Person(id_, username_, password_) 
{
    purse = purse_;
    phoneNumber = phoneNumber_;
    address = address_;
    isAdmin = false;
}

unordered_map<string, func_ptr> User::getCmdList()
{
    return userCmdList;
}

string User::getInfo(string del)
{
    ostringstream info;
    info << "id: " << to_string(id) << del 
         << "username: " << username << del
         << "password: " << password << del
         << "isAdmin: " << to_string(isAdmin) << del
         << "purse: " << purse << del
         << "phoneNumber: " << phoneNumber << del
         << "address: " << address << endl;
    return info.str();
}

void User::changeInfo(string newPassword, string newPhone, string newAddress) 
{
    if (password == newPassword || 
        phoneNumber == newPhone ||
        address == newAddress)
        throw Error(503);

    password = (newPassword == "") ?  password : newPassword;
    phoneNumber = (newPhone == "") ?  phoneNumber : newPhone;
    address = (newAddress == "") ?  address : newAddress;
}

int User::getPurse()
{
    return purse;
}

void User::checkout(int price)
{
    if(purse < price)
        throw Error(108);
    purse -= price;
}

void User::earn(int price)
{
    purse += price;
}

Admin::Admin(int id_,string username_, string password_) 
    : 
    Person(id_, username_, password_) 
{
    isAdmin = true;
}


unordered_map<string, func_ptr> Admin::getCmdList()
{
    return adminCmdList;
}

string Admin::getInfo(string del)
{
    ostringstream info;
    info << "id: " << to_string(id) << del 
         << "username: " << username << del
         << "password: " << password << del
         << "isAdmin: " << to_string(isAdmin) << endl;
    return info.str();
}

void Admin::changeInfo(string newPassword)
{
    if (password == newPassword)
        throw Error(503);
        
    password = newPassword;
}

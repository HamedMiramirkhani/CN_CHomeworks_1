#include <algorithm>

#include "person.hpp"
#include "dashboard.hpp"
#include "error.hpp"

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


void Person::changeInfo(string newPassword, string newPhone, string newAddress) {}

int Person::getID() {return id;}

User::User(int id_,std::string username_, 
    std::string password_, std::string purse_,
     std::string phoneNumber_, std::string address_)
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
    //return ;
}

string User::getInfo(string del)
{
    ostringstream info;
    info << "id: " << to_string(id) << del 
         << "username: " << username << del
         << "password: " << password << del
         << "is_admin: " << to_string(is_admin) << del
         << "purse: " << purse << del
         << "phoneNumber: " << phoneNumber << del
         << "address: " << address << endl;
    return info.str();
}

void User::changeInfo(std::string newPassword, std::string newPhone,
     std::string newAddress)
{
    if (password == newPassword || 
        phoneNumber == newPhone ||
        address == newAddress ||
        ! all_of(newPhone.begin(), newPhone.end(), ::isdigit))
        throw Error(503);

    password = (newPassword == "") ?  password : newPassword;
    phoneNumber = (newPhone == "") ?  phoneNumber : newPhone;
    address = (newAddress == "") ?  address : newAddress;
    throw Error(312);
}

Admin::Admin(int id_,string username_, string password_) 
    : 
    Person(id_, username_, password_) 
{ isAdmin = true;}


string Admin::getInfo(string del)
{
    ostringstream info;
    info << "id: " << to_string(id) << del 
         << "username: " << username << del
         << "password: " << password << del
         << "is_admin: " << to_string(isAdmin) << endl;
    return info.str();
}
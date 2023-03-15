#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include "classNames.hpp"
#include <string>

class Person {
public:
    Person (int id_,std::string username_, std::string password_);
    //..
protected:
    int id;
    std::string username;
    std::string password;
    bool isAdmin;
};

class User : public Person {
public:
    User(int id_,std::string username_, 
    std::string password_, std::string purse_,
     std::string phoneNumber_, std::string address_);
private:
    std::string purse;
    std::string phoneNumber;
    std::string address;
};

class Admin : public Person {
public:
    Admin(int id_,std::string username_, 
    std::string password_);
    
};

#endif

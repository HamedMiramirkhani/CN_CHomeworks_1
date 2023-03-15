#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include "classNames.hpp"
#include <string>

class Person {
public:
    Person (int id_,std::string username_, std::string password_);
    virtual std::unordered_map<std::string, func_ptr> getCmdList() = 0;
    bool checkInfo(std::string username_, std::string password_);
    virtual std::string getInfo(std::string del) = 0;
    virtual void changeInfo(std::string newPassword,
     std::string newPhone, std::string newAddress);
    int getID();
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

    std::unordered_map<std::string, func_ptr> getCmdList();
    std::string getInfo(std::string del);
    void changeInfo(std::string newPassword, std::string newPhone,
     std::string newAddress);

private:
    std::string purse;
    std::string phoneNumber;
    std::string address;
};

class Admin : public Person {
public:
    Admin(int id_,std::string username_, std::string password_);
    std::unordered_map<std::string, func_ptr> getCmdList();
    std::string getInfo(std::string del);
    void changeInfo(std::string newPassword);
};

#endif

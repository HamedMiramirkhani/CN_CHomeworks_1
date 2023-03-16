#pragma once

#include <string>
#include <unordered_map>
#include <sstream>

#include "classNames.hpp"

class Person {
public:
    Person (int id_,std::string username_, std::string password_);
    virtual std::unordered_map<std::string, func_ptr> getCmdList() = 0;
    bool checkInfo(std::string username_, std::string password_);
    bool hasUsername(std::string username_);
    bool hasID(int id_);
    virtual std::string getInfo(std::string del) = 0;
    virtual void changeInfo(std::string newPassword, std::string newPhone, std::string newAddress);
    virtual void changeInfo(std::string newPassword);
    int getID();
    virtual int getPurse();
    virtual void checkout(int price);
    virtual void earn(int price);
protected:
    int id;
    std::string username;
    std::string password;
    bool isAdmin;
};

class User : public Person {
public:
    User(int id_,std::string username_, std::string password_, int purse_, std::string phoneNumber_, std::string address_);
    std::unordered_map<std::string, func_ptr> getCmdList();
    std::string getInfo(std::string del);
    void changeInfo(std::string newPassword, std::string newPhone, std::string newAddress);
    int getPurse();
    void checkout(int price);
    void earn(int price);
private:
    int purse;
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

#ifndef __ROOM_H__
#define __ROOM_H__

#include <string>
#include <vector>

#include "person.hpp"

class Rent 
{
public:
    Rent(Person* person_, int numBeds_,std::string reserveDate_, std::string checkoutDate_);
    Person* person;
    int numBeds;
    std::string reserveDate;
    std::string checkoutDate;
};

class Room 
{
public:
    Room(int number_, int status_, int price_, int maxCapacity_, int capacity_, std::vector<Rent*> rents_);
    std::string getInfo(bool isAdmin);
    std::string getUsersInfo();
private:
    int number;
    int status;
    int price;
    int max_capacity;
    int capacity;
    std::vector<Rent*> rents;
};

class DateConfig
{
public:
    DateConfig(int day_, int month_, int year_);
    void passDay(std::string value);
    int day, month, year;
};

#endif
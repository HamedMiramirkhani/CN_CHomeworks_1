#pragma once

#include <string>
#include <vector>
#include <memory>

#include "person.hpp"

class DateConfig
{
public:
    DateConfig(int day_, int month_, int year_);
    void passDay(std::string value);
    int day, month, year;
};

class Rent 
{
public:
    Rent(Person* person_, int num_of_beds_,DateConfig reserveDate_, DateConfig checkoutDate_);
    bool isInReservation(DateConfig* today);
    std::string getReserveDate();
    std::string getCheckoutDate();
    void endRent(DateConfig* date);
    Person* person;
    int num_of_beds;
    DateConfig reserveDate;
    DateConfig checkoutDate;
};

class Room 
{
public:
    Room(int number_, int status_, int price_, int maxCapacity_, int capacity_, std::vector<std::shared_ptr<Rent>> rents_);
    std::string getInfo(DateConfig* today, bool isAdmin, int filter_empty_status);
    std::string getUsersInfo(DateConfig* today);
    bool has_room_num(int num);
    void changeInfo(std::string new_maxCapacity, std::string new_price);
    bool hasUser(DateConfig* today);
    void updateRoom(DateConfig* today);
    void addNewRent(int NumOfBeds, std::string CheckInDate, std::string CheckOutDate, Person* person, DateConfig* today);
    void checkBookOptions(int NumOfBeds, DateConfig CheckInDate, DateConfig* today);
    int calcOccupiedBeds(DateConfig* today);
    std::string checkReserved(int id);
    void cancelBook(int id, int number_of_canceling_bed, DateConfig* today);
    int findRent(int id);
    void checkCancelOptions(int number_of_canceling_bed, std::shared_ptr<Rent> rent, DateConfig* today);
    void leaveRoom(int id, DateConfig* today);
    void eject(int newCapacity, DateConfig* today);
private:
    int number;
    int status;
    int price;
    int maxCapacity;
    int capacity;
    std::vector<std::shared_ptr<Rent>> rents;
};
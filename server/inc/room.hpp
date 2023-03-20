#pragma once

#include "help.hpp"
#include "error.hpp"
#include "person.hpp"

class DateConfig
{
public:
    DateConfig(int day_, int month_, int year_);
    void pass_day(std::string value);
    int day, month, year;
};

class Room 
{
public:
    Room(int number_, int status_, int price_, int max_capacity_, int capacity_, std::vector<std::shared_ptr<Rent>> rents_);
    std::string get_info(DateConfig* today, bool is_admin, int filter_empty_status);
    std::string get_users_info(DateConfig* today);
    bool match_room_num(int num);
    void change_info(std::string new_max_capacity, std::string new_price);
    bool has_user(DateConfig* today);
    void update_room(DateConfig* today);
    void add_new_rent(int NumOfBeds, std::string CheckInDate, std::string CheckOutDate, Person* person, DateConfig* today);
    void check_book_options(int NumOfBeds, DateConfig CheckInDate, DateConfig* today);
    int calc_occupied_beds(DateConfig* today);
    std::string get_info_if_reserve(int id);
    void cancel_book(int id, int number_of_canceling_bed, DateConfig* today);
    int find_rent_index(int id);
    void check_cancel_options(int number_of_canceling_bed, std::shared_ptr<Rent> rent, DateConfig* today);
    void leave_room(int id, DateConfig* today);
    void eject(int new_capacity, DateConfig* today);
    FileDataContainers::RoomInfo get_data_for_write();
private:
    std::string convert_DataConfig_to_string(DateConfig data_config);
    long int calc_distance(DateConfig* date);
    long int calc_distance(DateConfig date);
    DateConfig convert_to_DataConfig(std::string str);
    int number;
    int status;
    int price;
    int max_capacity;
    int capacity;
    std::vector<std::shared_ptr<Rent>> rents;
};

class Rent 
{
public:
    Rent(Person* person_, int num_of_beds_,DateConfig reserveDate_, DateConfig checkoutDate_);
    bool is_in_reservation(DateConfig* today);
    std::string get_reserveDate();
    std::string get_checkoutDate();
    void end_rent(DateConfig* date);
    Person* person;
    int num_of_beds;
    DateConfig reserveDate;
    DateConfig checkoutDate;
    long int calc_distance(DateConfig* date);
    long int calc_distance(DateConfig date);
};
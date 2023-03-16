#include "room.hpp"
#include "manual.hpp"
#include "error.hpp"
#include "utils.hpp"

using namespace std;

Room::Room(int number_, int status_, int price_, int maxCapacity_, int capacity_, vector<std::shared_ptr<Rent>> rents_)
    :
    number(number_),
    status(status_),
    price(price_),
    maxCapacity(maxCapacity_),
    capacity(capacity_),
    rents(rents_)
{
}

string Room::getInfo(DateConfig* today, bool isAdmin, int filter_empty_status)
{
    if(filter_empty_status == EmptyFilterStatus::ENABLE && status == RoomStatus::FULL)
        return "";
    ostringstream info;
    info << "number: " << number << endl
         << "status: " << RoomStatus::str_form[status] << endl
         << "price: " << price << endl
         << "maxCapacity: " << maxCapacity << endl
         << "capacity: " << capacity << endl;
    
    if(isAdmin && capacity <= (maxCapacity/2))
        info << getUsersInfo(today);

    info << "################################" << endl;
    return info.str();
}

string Room::getUsersInfo(DateConfig* today)
{
    ostringstream info;
    info << "users:" << endl;
    for(auto rent : rents)
        if(rent->isInReservation(today))
            info << "   id: " << rent->person->getID() << endl
                 << "   num_of_beds: " << rent->num_of_beds << endl
                 << "   reserveDate: " << rent->getReserveDate() << endl
                 << "   checkoutDate: " << rent->getCheckoutDate() << endl;
    return info.str();
}

bool Room::has_room_num(int num)
{
    return num == number;
}

void Room::changeInfo(string new_maxCapacity, string new_price)
{
    if(new_maxCapacity != "" && stoi(new_maxCapacity) < (maxCapacity - capacity))
        throw Error(109);

    capacity += (new_maxCapacity == "") ? capacity : (stoi(new_maxCapacity) - maxCapacity);
    maxCapacity = (new_maxCapacity == "") ?  maxCapacity : stoi(new_maxCapacity);
    price = (new_price == "") ?  price : stoi(new_price);
}

bool Room::hasUser(DateConfig* today)
{
    for(auto rent : rents)
        if(Utils::calcDistance(today) <= Utils::calcDistance(rent->checkoutDate))
            return true;
    return false;
}

void Room::updateRoom(DateConfig* today)
{
    int occupied_beds = calcOccupiedBeds(today);
    capacity = maxCapacity - occupied_beds;
    status = (capacity == 0) ? RoomStatus::FULL : RoomStatus::EMPTY;
}

int Room::calcOccupiedBeds(DateConfig* today)
{
    int occupied_beds = 0;
    for(auto rent : rents)
        if(rent->isInReservation(today))
            occupied_beds += rent->num_of_beds;
    return occupied_beds;
}

void Room::addNewRent(int NumOfBeds, string CheckInDate, string CheckOutDate, Person* person, DateConfig* today)
{
    DateConfig CheckInDate_ = Utils::convertDataConfig(CheckInDate);
    DateConfig CheckOutDate_ = Utils::convertDataConfig(CheckOutDate);
    checkBookOptions(NumOfBeds, CheckInDate_, today);
    person->checkout(NumOfBeds * price);
    rents.push_back(make_shared<Rent>(person, NumOfBeds, CheckInDate_, CheckOutDate_));
}

void Room::checkBookOptions(int NumOfBeds, DateConfig CheckInDate, DateConfig* today)
{
    if(Utils::calcDistance(today) > Utils::calcDistance(CheckInDate))
        throw Error(503);
    if(NumOfBeds > maxCapacity)
        throw Error(503);
    if(NumOfBeds > (maxCapacity - calcOccupiedBeds(&CheckInDate)))
        throw Error(109);
}

string Room::checkReserved(int id)
{
    ostringstream info;
    for(auto rent : rents)
        if(rent->person->hasID(id))
            info << "room_number=" << number << ' ' 
                 << "num_of_beds=" << rent->num_of_beds << ' ' 
                 << "reserve_date=" << rent->getReserveDate() << ' '
                 << "checkout_date=" << rent->getCheckoutDate() << endl;
    return info.str();
}

void Room::cancelBook(int id, int number_of_canceling_bed, DateConfig* today)
{
    int rent_index = findRent(id);
    shared_ptr<Rent> rent = rents[rent_index];
    checkCancelOptions(number_of_canceling_bed, rent, today);
    if(rent->num_of_beds == number_of_canceling_bed)
        rents.erase(rents.begin() + rent_index);
    else
        rent->num_of_beds -= number_of_canceling_bed;
    
    rent->person->earn(number_of_canceling_bed * price / 2);
    updateRoom(today);
}

int Room::findRent(int id)
{
    for(unsigned int i = 0; i < rents.size(); i++)
        if(rents[i]->person->hasID(id))
            return i;
    throw Error(102);
}

void Room::checkCancelOptions(int number_of_canceling_bed, shared_ptr<Rent> rent, DateConfig* today)
{
    if(number_of_canceling_bed > rent->num_of_beds)
        throw Error(102);
    if(Utils::calcDistance(today) > Utils::calcDistance(rent->reserveDate))
        throw (Utils::calcDistance(today) <= Utils::calcDistance(rent->checkoutDate)) ? 
                Error(103) : Error(102);
}

void Room::leaveRoom(int id, DateConfig* today)
{
    int rent_index = findRent(id);
    shared_ptr<Rent> rent = rents[rent_index];
    if(!rent->isInReservation(today))
        throw Error(112);
    rent->endRent(today);
    updateRoom(today);
}

void Room::eject(int newCapacity, DateConfig* today)
{
    if(newCapacity > maxCapacity)
        throw Error(503);
    if((maxCapacity - capacity) > newCapacity)
    {
        int num_of_reject = (maxCapacity - capacity) - newCapacity;
        for(auto rent : rents)
        {
            if(num_of_reject <= 0) 
                break;
            num_of_reject -= rent->num_of_beds;
            rent->endRent(today);
        }
    }
    maxCapacity = newCapacity;
}

Rent::Rent(Person* person_, int num_of_beds_, DateConfig reserveDate_, DateConfig checkoutDate_)
    :
    person(person_),
    num_of_beds(num_of_beds_),
    reserveDate(reserveDate_),
    checkoutDate(checkoutDate_)
{
}

string Rent::getReserveDate()
{
    ostringstream info;
    info << reserveDate.day << '-'
         << reserveDate.month << '-'
         << reserveDate.year;
    return info.str();
}

string Rent::getCheckoutDate()
{
    ostringstream info;
    info << checkoutDate.day << '-'
         << checkoutDate.month << '-'
         << checkoutDate.year;
    return info.str();
}

bool Rent::isInReservation(DateConfig* today)
{
    long int check_in_distance = Utils::calcDistance(reserveDate), 
             check_out_distance = Utils::calcDistance(checkoutDate), 
             check_today = Utils::calcDistance(today);
    
    return (check_today >= check_in_distance && check_today <= check_out_distance);
}

void Rent::endRent(DateConfig* date)
{
    checkoutDate.day = date->day;
    checkoutDate.month = date->month;
    checkoutDate.year = date->year;
}


DateConfig::DateConfig(int day_, int month_, int year_)
    :
    day(day_),
    month(month_),
    year(year_)
{
}

void DateConfig::passDay(string value)
{
    for (int i = 0; i < stoi(value); i++)
    {
        day++;
        if(day == 31)
        {
            day = 1;
            month++;
        }
        if(month == 13)
        {
            month = 1;
            year++;
        }
    }
}
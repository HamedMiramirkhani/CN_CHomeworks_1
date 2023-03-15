#include "room.hpp"

using namespace std;

Room::Room(int number_, int status_, int price_, int maxCapacity_, int capacity_, vector<Rent*> rents_)
    :
    number(number_),
    status(status_),
    price(price_),
    max_capacity(maxCapacity_),
    capacity(capacity_),
    rents(rents_)
{}

string Room::getInfo(bool isAdmin)
{
    ostringstream info;
    info << "number: " << number << endl
         << "status: " << RoomStatus::str_form[status] << endl
         << "price: " << price << endl
         << "max_capacity: " << maxCapacity << endl
         << "capacity: " << capacity << endl;
    
    if(isAdmin && capacity <= (maxCapacity/2))
        info << getUsersInfo();

    info << "################################" << endl;
    return info.str();
}

string Room::getUsersInfo()
{
    ostringstream info;
    info << "users:" << endl;
    for(auto rent : rents)
        info << "   id: " << rent->person->getID() << endl
             << "   num_of_beds: " << rent->numBeds << endl
             << "   reserveDate: " << rent->reserveDate << endl
             << "   checkoutDate: " << rent->checkoutDate << endl;
    return info.str();
}

Rent::Rent(Person* person_, int numBeds_, string reserveDate_, string checkoutDate_)
    :
    person(person_),
    num_of_beds(numBeds_),
    reserveDate(reserveDate_),
    checkoutDate(checkoutDate_)
{    
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
            day = 0;
            month++;
        }
        if(month == 13)
        {
            month = 0;
            year++;
        }
    }
}
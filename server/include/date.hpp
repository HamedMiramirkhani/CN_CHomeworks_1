#ifndef _DATE_H_
#define _DATE_H_
#include "consts.hpp"

class Date
{
public:
    bool setDate(const std::string& dateStr);

private:
    int year;
    int month;
    int day;

    bool isValidDateFormat(const std::string& dateStr);
};

#endif
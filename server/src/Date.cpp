#include "../include/Date.hpp"

bool Date::setDate(const std::string &dateStr)
{
    if (!isValidDateFormat(dateStr))
    {
        return false;
    }

    this->day = std::stoi(dateStr.substr(0, 2));
    this->month = std::stoi(dateStr.substr(3, 2));
    this->year = std::stoi(dateStr.substr(6, 4));

    return true;
}

bool Date::isValidDateFormat(const std::string &dateStr)
{
    // Regular expression to match a date in the format DD/MM/YYYY
    std::regex dateRegex("\\d{2}/\\d{2}/\\d{4}");
    if(!std::regex_match(dateStr, dateRegex))
        return false;
    
    // Check if the range of the date is valid
    int day = std::stoi(dateStr.substr(0, 2));
    int month = std::stoi(dateStr.substr(3, 2));
    int year = std::stoi(dateStr.substr(6, 4));
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
        return false;

    return true;
}
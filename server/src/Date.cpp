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
    return std::regex_match(dateStr, dateRegex);
}
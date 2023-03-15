#ifndef __ERROR_HPP__
#define __ERROR_HPP__
#include "consts.hpp"

#include <string>

class Error
{
public:
    Error(int errorNumber , std::string extraInfo = "");
    std::string what(bool moreInfo = false);
private:
    int errorNumber;
    std::string extraInfo;
};

#endif
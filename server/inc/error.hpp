#pragma once

#include <string>

class Error
{
public:
    Error(int errorNum , std::string extraInfo = "");
    std::string what(bool moreInfo = false);
private:
    int errorNum;
    std::string extraInfo;
};

#pragma once
#include <string>

class ErrorCMD
{
public:
    ErrorCMD(std::string text_);
    std::string what();
private:
    std::string text;
};
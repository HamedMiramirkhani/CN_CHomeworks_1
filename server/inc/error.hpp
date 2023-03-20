#pragma once

#include <string>

class Error
{
public:
    Error(int error_number);
    std::string what();
private:
    int error_num;
};

class Message
{
public:
    Message(std::string text_);
    std::string what();
private:
    std::string text;
};

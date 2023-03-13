#ifndef __LOGGER_H__
#define __LOGGER_H__
#include "consts.hpp"

class Logger
{
public:
    Logger();
    void writeMsg(std::string message);
private:
    std::string fileName;
};

#endif
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>

class Logger
{
public:
    Logger();
    void writeMsg(std::string message);
private:
    std::string fileName;
};

#endif
#include "logger.hpp"

Logger::Logger(){ fileName = "log.txt"; }

void Logger::writeMsg(std::string message)
{
    std::ofstream lout;
    lout.open(fileName, std::ios::app);
    lout << message << "\n";
    lout.close();
}
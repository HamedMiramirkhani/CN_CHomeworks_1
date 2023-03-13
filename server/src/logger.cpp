#include "logger.hpp"

Logger::Logger() { fileName = LOGGER_FILE_NAME; }

void Logger::writeMsg(std::string message)
{
    std::ofstream lout;
    lout.open(fileName, std::ios::app);
    lout << message << "\n";
    lout.close();
}
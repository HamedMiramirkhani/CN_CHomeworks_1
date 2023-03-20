#include "logger.hpp"
#include "help.hpp"

using namespace std;

Logger::Logger()
{}

void Logger::log(std::string roll, int fd, std::string command)
{
	ofstream log_file;
	log_file.open(LOGGER_PATH, ios::app);
	time_t date = time(0);
	char* dt = ctime(&date);
	dt[strlen(dt) - 1] = '\0';
	log_file << '[' << dt << " " << roll << " with fd " << fd << "] " << command << endl;
	log_file.close();
}
#ifndef _CONSTS_
#define _CONSTS_

#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <dirent.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <fcntl.h>
#include <errno.h> 
#include <exception>
#include <chrono>
#include <ctime>  
#include <sys/select.h>

const std::string LOGGER_FILE_NAME = "log.txt";
const std::string CONFIG_FILE_NAME = "config.txt";
const std::string ROOM_FILE_NAME = "Roomsinfo.txt";
const std::string USER_FILE_NAME = "Usersinfo.txt";

#endif
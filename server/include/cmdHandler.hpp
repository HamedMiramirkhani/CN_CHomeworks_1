#ifndef __CMD_HANDLER_H__
#define __CMD_HANDLER_H__

#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <vector>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const int ERROR = -1;

class CmdHandler
{
public:
    CmdHandler();
    void runCommand(int fd, char* read_buffer);

private:
    std::vector<std::string> splitString(const std::string& s, char delimiter);

    class Fd_id
    {
    public:
        Fd_id(void);
        bool add(int fd, int id);
        int get(int fd);
        bool remove(int fd);
    
    private:
        std::map<int, int> map_fd_id;
    };

};

#endif
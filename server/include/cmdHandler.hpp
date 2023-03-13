#ifndef __CMD_HANDLER_H__
#define __CMD_HANDLER_H__
#include "consts.hpp"

const int ERROR = -1;

class CmdHandler
{
public:
    CmdHandler();
    void runCommand(int fd, char* read_buffer);

private:
    std::vector<std::string> splitString(const std::string& s, char delimiter);

    void signin(int fd, std::vector<std::string> splitted_buffer);

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
#include "cmdHandler.hpp"
#include <iostream>

CmdHandler::CmdHandler() 
{

}

CmdHandler::Fd_id::Fd_id(void) 
{

}

void CmdHandler::runCommand(int fd, char* read_buffer)
{
    std::cout << "fd: " << fd << "\n" << "read_buffer: " << read_buffer << std::endl;
}


bool CmdHandler::Fd_id::remove(int fd)
{
    auto result_find = map_fd_id.find(fd);
    if (result_find != map_fd_id.end())
    {
        map_fd_id.erase(result_find);
        return true;
    }
    else
        return false;
}

int CmdHandler::Fd_id::get(int fd)
{
    auto result_find = map_fd_id.find(fd);
    if (result_find != map_fd_id.end())
        return result_find->second;
    else
        return ERROR;
}

bool CmdHandler::Fd_id::add(int fd, int id)
{
    auto result_insert = map_fd_id.insert({fd, id});
    if (result_insert.second)
        return true;
    else
        return false;
}   
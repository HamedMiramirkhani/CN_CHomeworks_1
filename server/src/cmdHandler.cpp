#include "cmdHandler.hpp"
#include "consts.hpp"

CmdHandler::CmdHandler() 
{

}

CmdHandler::FdID::FdID(void) 
{

}

std::vector<std::string> CmdHandler::splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void CmdHandler::signin(int fd, std::vector<std::string> splitted_buffer)
{
    std::cout << "signin" << std::endl;
}

void CmdHandler::runCommand(int fd, char* read_buffer)
{    
    std::vector<std::string> splitted_buffer = splitString(std::string(read_buffer), ' ');

    if (splitted_buffer[0] == "signin")
    {
        signin(fd, splitted_buffer);
    }
    else
        std::cout << "Command not found" << std::endl;
}


bool CmdHandler::Fd_id::remove(int fd)
{
    auto resultFind = mapFdID.find(fd);
    if (resultFind != mapFdID.end())
    {
        mapFdID.erase(resultFind);
        return true;
    }
    else
        return false;
}

int CmdHandler::Fd_id::get(int fd)
{
    auto resultFind = mapFdID.find(fd);
    if (resultFind != mapFdID.end())
        return resultFind->second;
    else
        return ERROR;
}

bool CmdHandler::Fd_id::add(int fd, int id)
{
    auto resultInsert = mapFdID.insert({fd, id});
    if (resultInsert.second)
        return true;
    else
        return false;
}   
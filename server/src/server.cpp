#include "server.hpp"

Server::Server(const std::string& config_path,
 const std::string& rooms_path,
 const std::string& user_info_path)
    :
    jsonReader(JsonReader(config_path, rooms_path, user_info_path))
{
    //sth
}

void Server::run() {
    //sth
}
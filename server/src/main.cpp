#include "help.hpp"
#include "manager.hpp"
#include "server.hpp"

std::map<int,std::string> Info::status = Info::create_map();

int main(int argc, char const *argv[]) 
{
    Manager manager;
    Server server(& manager);
    server.start();
    server.run();
    return 0;
}

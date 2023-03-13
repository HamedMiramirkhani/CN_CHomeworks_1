#include "server.hpp"
#include "consts.hpp"

int main(int argc, char const *argv[])
{
    Server server = Server(CONFIG_FILE_NAME,
     ROOM_FILE_NAME, USER_FILE_NAME);
    server.run();
    return 0;
}
#include "server.hpp"

using namespace std;

const int CONFIG_PATH_INDX = 1;
const int ROOM_PATH_INDX = 2;
const int USERINFO_PATH_INDX = 3;

int main(int argc, char const *argv[]) {
    Server server = Server(argv[CONFIG_PATH_INDX], argv[ROOM_PATH_INDX], argv[USERINFO_PATH_INDX]);
    server.run();
    return 0;
}
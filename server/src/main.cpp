#include "server.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    Server server = Server();
    server.run();
    return 0;
}
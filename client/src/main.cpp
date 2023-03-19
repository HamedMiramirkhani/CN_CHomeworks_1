#include "../inc/client.hpp"

int main(int argc, char const *argv[]) 
{
    Client client;
    client.start();
    client.send_requests();
    return 0;
}
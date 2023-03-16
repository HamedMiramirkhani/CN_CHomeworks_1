// In the Name of God

#include "dashboard.hpp"
#include "manual.hpp"
#include "error.hpp"
#include "filehandler.hpp"
#include "utils.hpp"
#include "person.hpp"
#include "room.hpp"

using namespace std;

Dashboard::Dashboard(/* args */)
{
    lastID = 0;
    today = new DateConfig(23, 2, 2023);
    allUsers.push_back(new Admin(lastID++, "Admin", "Admin"));
    allUsers.push_back(new User(lastID++, "Morad", "1234", 1000, "00945692356", "Canada, Montral"));
    allUsers.push_back(new User(lastID++, "Jasem", "4321", 200, "00125692356", "United States, Newyork"));
    allUsers.push_back(new User(lastID++, "Pedram", "6789", 10, "00989112659874", "Iran, Rasht"));
    shared_ptr<Rent> t1 = make_shared<Rent>(allUsers[1], 1, DateConfig(25, 2, 2023), DateConfig(27, 2, 2023));
    shared_ptr<Rent> t2 = make_shared<Rent>(allUsers[2], 2, DateConfig(25, 2, 2023), DateConfig(27, 2, 2023));
    shared_ptr<Rent> t3 = make_shared<Rent>(allUsers[2], 1, DateConfig(27, 2, 2023), DateConfig(28, 2, 2023));
    shared_ptr<Rent> t4 = make_shared<Rent>(allUsers[3], 1, DateConfig(25, 2, 2023), DateConfig(26, 2, 2023));
    vector<shared_ptr<Rent>> r1, r2 = {t1}, r3 = {t2}, r4 = {t3, t4};
    allRooms.push_back(make_shared<Room>(101, RoomStatus::EMPTY, 100, 2, 2, r1));
    allRooms.push_back(make_shared<Room>(102, RoomStatus::EMPTY, 73, 3, 3, r2));
    allRooms.push_back(make_shared<Room>(201, RoomStatus::FULL, 100, 2, 2, r3));
    allRooms.push_back(make_shared<Room>(301, RoomStatus::EMPTY, 100, 1, 1, r4));
}

char *Dashboard::getResponse(int client_fd, char *request)
{
    char* response = new char[MAX_NAME_SIZE];
    strcat(response, "baba\n");
    try
    {
        throw Error(451);
        strcat(response, "dashboards response to client\n");
    }
    catch(Error& e)
    {
        strcat(response, "error massege\n");
    }

    return response;
}

bool Dashboard::connection_closed(int closed_client_fd)
{
    return false;
}

void Dashboard::addNewClient(int new_client_fd)
{
    printf("***\tNew costumer connected.fd=%d\t\n", new_client_fd);
    send(new_client_fd, "welcome to khane ghamar khanom", 31, 0);
    usersFdMap[new_client_fd] = nullptr;
}

void Dashboard::handle_command(int fd, string command)
{
    line = command;
    userFd = fd;
    string command_key = Utils::splitLine(command, ' ');
    try
    {
        auto command_list = getCmdList(userFd);
        route_command(command_key, command_list);
    } 
    catch (Error& error) 
    {
        write(STD_OUT, error.what().c_str(),strlen(error.what().c_str()));
        write(STD_OUT, "\n",strlen("\n"));
    }
}

unordered_map<string, func_ptr> Dashboard::getCmdList(int fd)
{
    Person* person = usersFdMap[fd];
    return (person == nullptr) ? unregisteredUserList : person->getCmdList();
}

void Dashboard::route_command(string cmd, const unordered_map<string, func_ptr> &list)
{
    auto func = list.find(cmd);
    if (func == list.end()) throw Error(403);
    (this->*(func->second))();
}

#include "dashboard.hpp"
#include "manual.hpp"
#include "error.hpp"
#include "filehandler.hpp"
#include "Utils.hpp"
#include "person.hpp"
#include "room.hpp"

using namespace std;

void Dashboard::signup()
{
    string username, password, purse, phone, address;
    username = Utils::getParam(line, "username");
    password = Utils::getParam(line, "password");
    purse = Utils::getParam(line, "purse");
    phone = Utils::getParam(line, "phone");
    address = Utils::getParam(line, "address");
    checkExistUsername(username);
    allUsers.push_back(new User(lastID++, username, password, stoi(purse), phone, address));
    throw Error(231);
}

void Dashboard::checkExistUsername(string username)
{
    for(auto person : allUsers)
        if (person->hasUsername(username))
            throw Error(451);
}

void Dashboard::signin()
{
    string username, password;
    username = Utils::getParam(line, "username");
    password = Utils::getParam(line, "password");
    findSignedInUser(username, password);
    throw Error(230);
}

void Dashboard::findSignedInUser(string username, string password)
{
    for(auto person : allUsers)
        if (person->checkInfo(username, password))
        {
            usersFdMap[userFd] = person;
            return;
        }
    throw Error(430);
}

void Dashboard::viewUserInformation()
{
    cout << usersFdMap[userFd]->getInfo("\n");
}

void Dashboard::viewAllUsers()
{
    ostringstream info;
    for(auto user : allUsers)
        info << user->getInfo(" || ");
    cout << info.str();
}

void Dashboard::viewRoomsInfoForUser()
{
    int filter_empty_status;
    filter_empty_status = (Utils::getParam(line, "filter_empty", false) == "") ? 
                            EmptyFilterStatus::DISABLE : EmptyFilterStatus::ENABLE;
    
    getRoomsInfo(false, filter_empty_status);
}

void Dashboard::viewRoomsInfoForAdmin()
{
    getRoomsInfo(true, EmptyFilterStatus::DISABLE);
}

void Dashboard::getRoomsInfo(bool isAdmin, int filter_empty_status)
{
    ostringstream info;
    info << "-----------------------------------------------" <<endl;
    for(auto room : allRooms)
        info << room->getInfo(today, isAdmin, filter_empty_status);
    info << "-----------------------------------------------" <<endl;
    cout << info.str();
}

void Dashboard::book()
{
    string RoomNum, NumOfBeds, CheckInDate, CheckOutDate;
    RoomNum = Utils::getParam(line, "RoomNum");
    NumOfBeds = Utils::getParam(line, "NumOfBeds");
    CheckInDate = Utils::getParam(line, "CheckInDate");
    CheckOutDate = Utils::getParam(line, "CheckOutDate");
    bookOptions(stoi(RoomNum), stoi(NumOfBeds), CheckInDate, CheckOutDate);
    throw Error(110);
}

void Dashboard::bookOptions(int RoomNum,int NumOfBeds, string CheckInDate, string CheckOutDate)
{
    int room_index = findRoom(RoomNum);
    allRooms[room_index]->addNewRent(NumOfBeds, CheckInDate, CheckOutDate, 
                                        usersFdMap[userFd], today);
    allRooms[room_index]->updateRoom(today);
}

void Dashboard::showReservations()
{
    ostringstream list;
    list << "-----------------------------------------------" << endl
         << "today: " << today->day << '-' << today->month << '-' << today->year << endl
         << "your money: " << usersFdMap[userFd]->getPurse() << endl
         << "your_reservations:" << endl;
    for(auto room : allRooms)
        list << room->checkReserved(usersFdMap[userFd]->getID());
    list << "-----------------------------------------------" <<endl;
    cout << list.str();
}

void Dashboard::cancel()
{
    string RoomNum, Num;
    RoomNum = Utils::getParam(line, "RoomNum");
    Num = Utils::getParam(line, "Num");
    int room_index = findRoom(stoi(RoomNum)), id = usersFdMap[userFd]->getID();
    allRooms[room_index]->cancelBook(id, stoi(Num), today);
    throw Error(106);
}

void Dashboard::passDay()
{
    string value;
    value = Utils::getParam(line, "value");
    today->passDay(value);
    updateRooms();
    throw Error(110);
}

void Dashboard::updateRooms()
{
    for(auto room : allRooms)
        room->updateRoom(today);
}

void Dashboard::editInfoForUser()
{
    string newPassword, phone, address;
    newPassword = Utils::getParam(line, "newPassword", false);
    phone = Utils::getParam(line, "phone", false);
    address = Utils::getParam(line, "address", false);
    usersFdMap[userFd]->changeInfo(newPassword, phone, address);
    throw Error(312);
}

void Dashboard::editInfoForAdmin()
{
    string newPassword, phone, address;
    newPassword = Utils::getParam(line, "newPassword");
    usersFdMap[userFd]->changeInfo(newPassword);
    throw Error(312);
}

void Dashboard::leavingRoomForUser()
{
    string value;
    value = Utils::getParam(line, "value");
    int room_index = findRoom(stoi(value)), id = usersFdMap[userFd]->getID();
    allRooms[room_index]->leaveRoom(id, today);
    throw Error(413);
}

void Dashboard::leavingRoomForAdmin()
{
    string value, newCapacity;
    value = Utils::getParam(line, "value");
    newCapacity = Utils::getParam(line, "newCapacity");
    int room_index = findRoom(stoi(value));
    allRooms[room_index]->eject(stoi(newCapacity), today);
    allRooms[room_index]->updateRoom(today);
    throw Error(110);
}

void Dashboard::rooms()
{
    string room_command_request;
    room_command_request = Utils::getParam(line, "room_command_request");
    route_command(room_command_request, roomsCmdList);
}

void Dashboard::roomsAdd()
{
    string RoomNum, Max_Capacity, Price;
    RoomNum = Utils::getParam(line, "RoomNum");
    Max_Capacity = Utils::getParam(line, "Max_Capacity");
    Price = Utils::getParam(line, "Price");
    checkExistRoom(RoomNum);
    allRooms.push_back(make_shared<Room>(stoi(RoomNum), RoomStatus::EMPTY, stoi(Price), stoi(Max_Capacity),
                                          stoi(Max_Capacity), vector<shared_ptr<Rent>>{}));
    throw Error(104);
}

void Dashboard::checkExistRoom(string RoomNum)
{
    for (auto room : allRooms)
        if(room->has_room_num(stoi(RoomNum)))
            throw Error(111);
}

void Dashboard::roomsChange()
{
    string RoomNum, new_Max_Capacity, new_Price;
    RoomNum = Utils::getParam(line, "RoomNum", false);
    new_Max_Capacity = Utils::getParam(line, "Max_Capacity", false);
    new_Price = Utils::getParam(line, "Price", false);
    int room_index = findRoom(stoi(RoomNum));
    allRooms[room_index]->changeInfo(new_Max_Capacity, new_Price);
    throw Error(105);
}

void Dashboard::roomsRemove()
{
    string RoomNum;
    RoomNum = Utils::getParam(line, "RoomNum");
    int room_index = findRoom(stoi(RoomNum));
    checkRoomEmpty(room_index);
    allRooms.erase(allRooms.begin() + room_index);
    throw Error(106);
}

void Dashboard::checkRoomEmpty(int room_index)
{
    if(allRooms[room_index]->hasUser(today))
        throw Error(109);
}

int Dashboard::findRoom(int room_num)
{
    for(unsigned int i = 0; i < allRooms.size(); i++)
        if(allRooms[i]->has_room_num(room_num))
            return i;
    throw Error(101);
}

void Dashboard::logout()
{
    usersFdMap[userFd] = nullptr;
    throw Error(201);
}
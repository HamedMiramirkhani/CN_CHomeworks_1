#pragma once

class Error;
class Dashboard;
class Person;
class User;
class Admin;
class Room;
class Server;
class Rent;
class DateConfig;
//https://stackoverflow.com/questions/4295432/typedef-function-pointer
typedef void (Dashboard::*funcPtr)();
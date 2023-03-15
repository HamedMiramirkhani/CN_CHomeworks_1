#include <algorithm>

#include "person.hpp"
#include "dashboard.hpp"
#include "error.hpp"

using namespace std;

Person::Person(int id_,string username_, string password_)
    :
    id(id_),
    username(username_),
    password(password_)
{
}


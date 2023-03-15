// In the Name of God

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <vector>
#include "filehandler.hpp"

using namespace std;

Json::Value FileHandler::get_date(Date date)
{
    Json::Value root;
    root["day"] = date.day;
    root["month"] = date.month;
    root["year"] = date.year;
    return root;
}




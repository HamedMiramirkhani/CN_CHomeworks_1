#include <iostream>

#include "utils.hpp"
#include "error.hpp"
#include "room.hpp"

using namespace std;

string Utils::splitLine(string str, char del) 
{
    str.append(" ");
    string res = "";
    istringstream sstream(str);
    getline(sstream, res, del);
    str = str.substr(res.size() + 1);
    return res;
}

string Utils::getParam(string line, string key, bool required) 
{
    vector<string> words = makeLineList(line, ' ');
    auto it = find(words.begin(), words.end(), key);
    if (it == words.end())
    {
        if (required)
            throw exception();
        else
            return "";
    }
    auto index = distance(words.begin(), it);
    return words[index + 1];
}

vector<string> Utils::makeLineList(string line, char divider) 
{
    vector<string> dividedLine;
    string argument;
    istringstream arguments(line);
    while (getline(arguments, argument, divider)) {
        if (argument == "")
            continue;
        dividedLine.push_back(argument);
    }
    return dividedLine;
}

void Utils::checkIsNum(string a)
{
    if(! all_of(a.begin(), a.end(), ::isdigit))
        throw Error(503);
}

DateConfig Utils::convertDataConfig(string str)
{
    str.push_back('-');
    istringstream arguments(str);
    string day, month, year;
    getline(arguments, day, '-');
    getline(arguments, month, '-');
    getline(arguments, year, '-');
    return DateConfig(stoi(day), stoi(month), stoi(year));
}

long int Utils::calcDistance(DateConfig* date)
{
    return date->year*360 + date->month*30 + date->day;
}

long int Utils::calcDistance(DateConfig date)
{
    return date.year*360 + date.month*30 + date.day;
}

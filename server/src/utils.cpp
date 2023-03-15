#include "Utils.hpp"

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
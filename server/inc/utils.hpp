#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

#include "classNames.hpp"

namespace Utils {
    std::string splitLine(std::string str, char del);
    std::vector<std::string> makeLineList(std::string line, char divider);
    std::string getParam(std::string line, std::string key, bool required=true);
    void checkIsNum(std::string a);
    DateConfig convertDataConfig(std::string str);
    long int calcDistance(DateConfig* date);
    long int calcDistance(DateConfig date);
}
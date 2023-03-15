#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

namespace Utils {
    std::string parse_line(std::string str, char del);
    std::vector<std::string> makeLineList(std::string line, char divider);
    std::string getParam(std::string line, std::string key, bool required=true);
}

#endif
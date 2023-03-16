#include <iostream>
#include <string>
#include "../inc/error.hpp"
#include "../inc/manual.hpp"

using namespace std;

Error::Error (int errorNum , string extraInfo)
    :
    errorNum(errorNum),
    extraInfo(extraInfo)
{
}

string Error::what(bool moreInfo)
{
    string error_msg = "Error " + to_string(errorNum) + 
                    ": " + Info::status[errorNum];

    return moreInfo ? error_msg + " -- " + extraInfo : error_msg;
}

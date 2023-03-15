#include <iostream>
#include <string>
#include "error.hpp"

using namespace std;

Error::Error (int errorNumber , string extraInfo)
    :
    errorNumber(errorNumber),
    extraInfo(extraInfo)
{
}

string Error::what(bool moreInfo)
{
    string errorMsg = "Error " + to_string(errorNumber) + 
                    ": " + Info::status[errorNumber];

    return moreInfo ? errorMsg + " -- " + extraInfo : errorMsg;
}
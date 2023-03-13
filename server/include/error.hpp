#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__
#include "consts.hpp"

class Exception
{
public:
    std::string show();
private:
    const std::string msg;
};

#endif
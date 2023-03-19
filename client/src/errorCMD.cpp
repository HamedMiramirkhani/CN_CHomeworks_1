#include "errorCMD.hpp"

ErrorCMD::ErrorCMD(std::string text_)
    :
    text(text_)
{    
}

std::string ErrorCMD::what()
{
    return text;
}
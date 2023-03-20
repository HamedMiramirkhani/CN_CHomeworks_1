#include "error.hpp"
#include "help.hpp"

using namespace std;

Error::Error (int error_num_): error_num(error_num_) {}

string Error::what()
{
    string red_color = RED_COLOR,
    white_color = WHITE_COLOR;

    string msg = red_color + 
    "Error " + to_string(error_num) + ": " + 
    Info::status[error_num] + white_color;

    return msg;
}

Message::Message(string text_): text(text_) {}

string Message::what() { return text; }

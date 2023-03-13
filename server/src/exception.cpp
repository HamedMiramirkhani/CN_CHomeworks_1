#include "exception.hpp"

std::string Exception::getError() 
{return;}

std::string TheDesiredRoomWasNotFound::getError()
{return to_string(num) + error;}

std::string YourReservationWasNotFound::getError()
{return to_string(num) + error;}

std::string SuccessfullyAdded::getError()
{return to_string(num) + error;}

std::string SuccessfullyModified::getError()
{return to_string(num) + error;}

std::string SuccessfullyDeleted::getError()
{return to_string(num) + error;}

std::string YourAccountBalanceIsNotEnough::getError()
{return to_string(num) + error;}

std::string TheRoomCapacityIsFull::getError()
{return to_string(num) + error;}

std::string SuccessfullyDone::getError()
{return to_string(num) + error;}

std::string ThisRoomAlreadyExists::getError()
{return to_string(num) + error;}

std::string UserLoggedOutSuccessfully::getError()
{return to_string(num) + error;}

std::string UserLoggedIn::getError()
{return to_string(num) + error;}

std::string UserSuccessfullySignup::getError()
{return to_string(num) + error;}

std::string UserSignedUp::getError()
{return to_string(num) + error;}

std::string InformationWasChangedSuccessfully::getError()
{return to_string(num) + error;}

std::string InvalidValue::getError()
{return to_string(num) + error;}

std::string AccessDenied::getError()
{return to_string(num) + error;}

std::string InvalidCapacityValue::getError()
{return to_string(num) + error;}

std::string SuccessfullyLeaving::getError()
{return to_string(num) + error;}

std::string InvalidUsernameOrPassword::getError()
{return to_string(num) + error;}

std::string UserAlreadyExists::getError()
{return to_string(num) + error;}

std::string BadSequenceOfCommands::getError()
{return to_string(num) + error;}

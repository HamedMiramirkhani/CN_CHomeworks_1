#include "exception.hpp"

std::string Exception::getError() 
{return "";}

std::string TheDesiredRoomWasNotFound::getError()
{return std::to_string(num) + error;}

std::string YourReservationWasNotFound::getError()
{return std::to_string(num) + error;}

std::string SuccessfullyAdded::getError()
{return std::to_string(num) + error;}

std::string SuccessfullyModified::getError()
{return std::to_string(num) + error;}

std::string SuccessfullyDeleted::getError()
{return std::to_string(num) + error;}

std::string YourAccountBalanceIsNotEnough::getError()
{return std::to_string(num) + error;}

std::string TheRoomCapacityIsFull::getError()
{return std::to_string(num) + error;}

std::string SuccessfullyDone::getError()
{return std::to_string(num) + error;}

std::string ThisRoomAlreadyExists::getError()
{return std::to_string(num) + error;}

std::string UserLoggedOutSuccessfully::getError()
{return std::to_string(num) + error;}

std::string UserLoggedIn::getError()
{return std::to_string(num) + error;}

std::string UserSuccessfullySignup::getError()
{return std::to_string(num) + error;}

std::string UserSignedUp::getError()
{return std::to_string(num) + error;}

std::string InformationWasChangedSuccessfully::getError()
{return std::to_string(num) + error;}

std::string InvalidValue::getError()
{return std::to_string(num) + error;}

std::string AccessDenied::getError()
{return std::to_string(num) + error;}

std::string InvalidCapacityValue::getError()
{return std::to_string(num) + error;}

std::string SuccessfullyLeaving::getError()
{return std::to_string(num) + error;}

std::string InvalidUsernameOrPassword::getError()
{return std::to_string(num) + error;}

std::string UserAlreadyExists::getError()
{return std::to_string(num) + error;}

std::string BadSequenceOfCommands::getError()
{return std::to_string(num) + error;}

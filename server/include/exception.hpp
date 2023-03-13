#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__
#include "consts.hpp"

class Exception
{
    public:
        virtual std::string getError();
};

class TheDesiredRoomWasNotFound : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 101;
        const std::string error = ": The desired room was not found.";
};

class YourReservationWasNotFound : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 102;
        const std::string error = ": Your reservation was not found.";
};

class SuccessfullyAdded : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 104;
        const std::string error = ": Successfully added.";
};

class SuccessfullyModified : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 105;
        const std::string error = ": Successfully modified.";
};

class SuccessfullyDeleted : public Exception
{
    public:
        virtual std::string getError();
    
    private:
        const int num = 106;
        const std::string error = ": Successfully deleted.";
};

class YourAccountBalanceIsNotEnough : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 108;
        const std::string error = ": Your account balance is not enough.";
};

class TheRoomCapacityIsFull : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 109;
        const std::string error = ": The room capacity is full.";
};

class SuccessfullyDone : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 110;
        const std::string error = ": Successfully done.";
};

class ThisRoomAlreadyExists : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 111;
        const std::string error = ": This room already exists.";
};

class UserLoggedOutSuccessfully : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 201;
        const std::string error = ": User logged out successfully.";
};

class UserLoggedIn : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 230;
        const std::string error = ": User logged in.";
};

class UserSuccessfullySignup : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 231;
        const std::string error = ": User successfully signup.";
};

class UserSignedUp : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 311;
        const std::string error = ": User signed up.Enter your password, purse, phone and address.";
};

class InformationWasChangedSuccessfully : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 312;
        const std::string error = ": Information was changed successfully.";
};

class InvalidValue : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 401;
        const std::string error = ": Invalid value.";
};

class AccessDenied : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 403;
        const std::string error = ": Access denied.";
};

class InvalidCapacityValue : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 412;
        const std::string error = ": Invalid capacity value.";
};

class SuccessfullyLeaving : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 413;
        const std::string error = ": Successfully leaving.";
};

class InvalidUsernameOrPassword : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 430;
        const std::string error = ": Invalid username or password.";
};

class UserAlreadyExists : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 451;
        const std::string error = ": User already exists.";
};

class BadSequenceOfCommands : public Exception
{
    public:
        virtual std::string getError();

    private:
        const int num = 503;
        const std::string error = ": bad sequence of commands.";
};

#endif
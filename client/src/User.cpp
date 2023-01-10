#include "../include/User.h"

User::User() : receiptIdCounter(0), username("")
{
}

int User::assignRId()
{
    return receiptIdCounter++;
}

std::string User::getUserName()
{
    return username;
}

void User::setUserName(std::string newUsername)
{
    username = newUsername;
}

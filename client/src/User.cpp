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

void User::addReciept(int receiptId, std::string frameType)
{
    reciepts[receiptId] = frameType;
}

std::string User::getReciept(int receiptId)
{
    return reciepts[receiptId];
}

void User::removeReciept(int receiptId)
{
    reciepts.erase(receiptId);
}

void User::resetUser()
{
    receiptIdCounter = 0;
    username = "";
}
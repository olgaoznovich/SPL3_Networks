#include "../include/User.h"

User::User() : receiptIdCounter(0), username(""), subIdCounter(0), subs(), reciepts()
{
}

int User::assignRId()
{
    return receiptIdCounter++;
}

int User::assignSId()
{
    return subIdCounter++;
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

void User::addSub(int subId, std::string gameName)
{
    subs[subId] = gameName;
}

std::string User::getSub(int subId)
{
    return subs[subId];
}

void User::removeSub(int subId)
{
    subs.erase(subId);
}

void User::resetUser()
{
    receiptIdCounter = 0;
    username = "";
    subIdCounter = 0;
    //add reset to the dicts
}
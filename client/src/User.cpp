#include "../include/User.h"

User::User() : receiptIdCounter(0), subIdCounter(0), username(""), receipts(), subsId2Game(), subsGame2Id()
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
    receipts[receiptId] = frameType;
}

std::string User::getReciept(int receiptId)
{
    return receipts[receiptId];
}

void User::removeReciept(int receiptId)
{
    receipts.erase(receiptId);
}

void User::addSubId2Game(int subId, std::string gameName)
{
    subsId2Game[subId] = gameName;
}

std::string User::getSubId2Game(int subId)
{
    return subsId2Game[subId];
}

void User::removeSubId2Game(int subId)
{
    subsId2Game.erase(subId);
}

void User::addSubGame2Id(std::string gameName, int subId)
{
    subsGame2Id[gameName] = subId;
}

int User::getSubGame2Id(std::string gameName)
{
    if(subsGame2Id.count(gameName) > 0) {
        return subsGame2Id[gameName];    
    }
    return -1;
    
}

void User::removeSubGame2Id(std::string gameName)
{
    subsGame2Id.erase(gameName);
}

void User::resetUser()
{
    receiptIdCounter = 0;
    username = "";
    subIdCounter = 0;
    //add reset to the dicts
    subsGame2Id.clear();
    subsId2Game.clear();
    receipts.clear();
}
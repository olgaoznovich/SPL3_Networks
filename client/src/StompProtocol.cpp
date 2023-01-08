#include "../include/StompProtocol.h"

StompProtocol::StompProtocol() {}

std::string StompProtocol::createFrame(std::string command) 
{

}

std::string StompProtocol::parseFrame(std::string frame)
{

}

bool StompProtocol::getShouldTerminate()
{
    return shouldTerminate;
}

void StompProtocol::setShouldTerminate(bool value)
{
    shouldTerminate = value;
}   
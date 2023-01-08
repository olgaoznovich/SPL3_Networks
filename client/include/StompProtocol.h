#pragma once

#include "../include/ConnectionHandler.h"
#include <string>


// TODO: implement the STOMP protocol
class StompProtocol
{
private:
    bool shouldTerminate;
public:
    StompProtocol();
    std::string createFrame(std::string command);
    std::string parseFrame(std::string frame);
    bool getShouldTerminate();
    void setShouldTerminate(bool value);
};

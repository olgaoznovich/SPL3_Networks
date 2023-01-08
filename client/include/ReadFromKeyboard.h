#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"


class ReadFromKeyboard
{
public:
    ReadFromKeyboard(ConnectionHandler &conHandler, StompProtocol &protocol);
    void Run();

private:
    ConnectionHandler &conHandler;
    bool shouldTerminate;
    StompProtocol &protocol;
};
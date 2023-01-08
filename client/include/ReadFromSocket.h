#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"


class ReadFromSocket
{
public:
    ReadFromSocket(ConnectionHandler &conHandler, StompProtocol &protocol);
    void Run();

private:
    ConnectionHandler &conHandler;
    bool shouldTerminate;
    StompProtocol &protocol;

};

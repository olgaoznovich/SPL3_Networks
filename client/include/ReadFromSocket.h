#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"
#include "../include/User.h"


class ReadFromSocket
{
public:
    ReadFromSocket(ConnectionHandler &conHandler, StompProtocol &protocol, User &user);
    void Run();

private:
    ConnectionHandler &conHandler;
    bool shouldTerminate;
    StompProtocol &protocol;
    User &user;
};

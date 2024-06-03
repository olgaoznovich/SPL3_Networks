#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/StompProtocol.h"
#include "../include/User.h"
#include "../include/GameTracker.h"


class ReadFromSocket
{
public:
    ReadFromSocket(ConnectionHandler &conHandler, StompProtocol &protocol, User &user, GameTracker &gameTracker);
    void Run();

private:
    ConnectionHandler &conHandler;
    bool shouldTerminate;
    StompProtocol &protocol;
    User &user;
    GameTracker &gameTracker;
};

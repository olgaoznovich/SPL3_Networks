#pragma once

#include "../include/ConnectionHandler.h"

class ReadFromSocket
{
public:
    ReadFromSocket(ConnectionHandler &conHandler);
    void Run();
    
private:
    ConnectionHandler &conHandler;

};

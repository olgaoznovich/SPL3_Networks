#pragma once

#include "../include/ConnectionHandler.h"
#include <string>
#include <vector>


// TODO: implement the STOMP protocol
class StompProtocol
{
private:
    bool shouldTerminate;
    std::vector<std::string> split(std::string s, char del);
    std::string processLogin(std::vector<std::string> vec);
    std::string processJoin(std::vector<std::string> vec);
    std::string processExit(std::vector<std::string> vec);
    std::string processReport(std::vector<std::string> vec);
    std::string processSummary(std::vector<std::string> vec);
    std::string processLogout(std::vector<std::string> vec);

public:
    StompProtocol();
    std::string createFrame(std::string command);
    std::string parseFrame(std::string frame);
    bool getShouldTerminate();
    void setShouldTerminate(bool value);
    std::vector<std::string> isLoginCommand(std::string command);

};

#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/User.h"
#include "../include/GameTracker.h"

#include <string>
#include <vector>
#include <queue>


// TODO: implement the STOMP protocol
class StompProtocol
{
private:
    bool shouldTerminate;
    std::vector<std::string> split(std::string s, char del);
    std::string processLogin(std::vector<std::string> vec, User &user);
    std::string processJoin(std::vector<std::string> vec, User &user);
    std::string processExit(std::vector<std::string> vec, User &user);
    std::queue<std::string> processReport(std::vector<std::string> vec, User &user);
    void processSummary(std::vector<std::string> vec, GameTracker &gameTracker);
    std::string processLogout(std::vector<std::string> vec, User &user);
    std::string printfMap(const std::map<std::string, std::string> &map);


public:
    StompProtocol();
    std::queue<std::string> createFrame(std::string command, User &user, GameTracker &gameTracker);
    std::string parseFrame(std::string frame, User &user, GameTracker &gameTracker);
    bool getShouldTerminate();
    void setShouldTerminate(bool value);
    std::vector<std::string> isLoginCommand(std::string command);
    bool isErrorFrame(std::string frame);
    int getReciptId(std::string frame);
};

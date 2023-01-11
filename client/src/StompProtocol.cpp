#include "../include/StompProtocol.h"
using namespace std;

StompProtocol::StompProtocol() {}

std::string StompProtocol::createFrame(std::string command) 
{
    //we assume the command input is legal
    vector<string> strComps = split(command, ' ');
    string keyword = strComps.at(0);
    string output = "";
    if(keyword == "login") 
    {
        output = processLogin(strComps);
    } else if (keyword == "join")
    {
        processJoin(strComps);
    } else if (keyword == "exit")
    {

    } else if (keyword == "report")
    {

    } else if (keyword == "summary")
    {

    } else if (keyword == "logout")
    {

    } 

    return output;
}

std::string StompProtocol::parseFrame(std::string frame)
{
    vector<string> strComps = split(frame, '\n');
    string keyword = strComps.at(0);
    string output = "";
    if(keyword == "CONNECTED") {
        output = "login successful";
    }
    return output;
}



bool StompProtocol::getShouldTerminate()
{
    return shouldTerminate;
}

void StompProtocol::setShouldTerminate(bool value)
{
    shouldTerminate = value;
}   


std::vector<std::string> StompProtocol::split(std::string s, char del)
{
    std::vector<std::string> vector;

    std::stringstream ss(s);
    std::string word;
    while(!ss.eof()) 
    {
        std::getline(ss, word, del);
        vector.push_back(word);
    }

    return vector;
}

string StompProtocol::processLogin(vector<string> vec)
{
    //build CONNECT frame
    return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + vec.at(2) + "\npasscode:" + vec.at(3) + "\n\n" + '\0';
} 

string StompProtocol::processJoin(vector<string> vec)
{
    return "";
} 

string StompProtocol::processExit(vector<string> vec)
{
    return "";
} 

string StompProtocol::processReport(vector<string> vec)
{
    return "";
} 

string StompProtocol::processSummary(vector<string> vec)
{
    return "";
} 

string StompProtocol::processLogout(vector<string> vec)
{
    return "";
} 

vector<string> StompProtocol::isLoginCommand(std::string command)
{
    vector<string> strComps = split(command, ' ');
    vector<string> output;
    if(strComps.at(0) == "login")
    {
        return split(strComps.at(1), ':');
    }

    return output;
}

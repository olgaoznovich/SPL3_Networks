#include "../include/StompProtocol.h"
using namespace std;

StompProtocol::StompProtocol() {}

std::string StompProtocol::createFrame(std::string command, User &user) 
{
    //we assume the command input is legal
    vector<string> strComps = split(command, ' ');
    string keyword = strComps.at(0);
    string output = "";
    if(keyword == "login") 
    {
        output = processLogin(strComps, user);
    } else if (keyword == "join")
    {
        output = processJoin(strComps, user);
    } else if (keyword == "exit")
    {
        output = processExit(strComps, user);
    } else if (keyword == "report")
    {

    } else if (keyword == "summary")
    {

    } else if (keyword == "logout")
    {
        output = processLogout(strComps, user);
    } 

    return output;
}

std::string StompProtocol::parseFrame(std::string frame, User &user)
{
    vector<string> strComps = split(frame, '\n');
    string keyword = strComps.at(0);
    string output = "";
    if(keyword == "CONNECTED") {
        output = "login successful";
    } else if (keyword == "RECEIPT") {
        int rId = getReciptId(frame);
        output = user.getReciept(rId);
    } else if (keyword == "ERROR") {
        output = strComps.at(strComps.size() - 2); //todo: handle the rest!
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

string StompProtocol::processLogin(vector<string> vec, User &user)
{
    //build CONNECT frame
    // return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + vec.at(2) + "\npasscode:" + vec.at(3) + "\n\n" + '\0';
    user.setUserName(vec.at(2));

    return "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + 
            vec.at(2) + "\npasscode:" + vec.at(3) + "\n\n"; 
            //removed null char bc sendAsciiFrame adds it automatically
} 


string StompProtocol::processJoin(vector<string> vec, User &user)
{
    int rId = user.assignRId();
    int sId = user.assignSId();
    std::string gameName = vec.at(1);
    user.addReciept(rId, "joined " + gameName);
    user.addSubId2Game(sId, gameName);
    user.addSubGame2Id(gameName, sId);
    return "SUBSCRIBE\ndestination:/" + gameName + "\nid:" + std::to_string(sId) + "\nreceipt:" + std::to_string(rId) + "\n\n";
} 

string StompProtocol::processExit(vector<string> vec, User &user)
{
    int rId = user.assignRId();
    std::string gameName = vec.at(1);
    user.addReciept(rId, "Exited channel" + gameName);
    int sId = user.getSubGame2Id(gameName);
    if(sId >= 0) {
        user.removeSubId2Game(sId);
        user.removeSubGame2Id(gameName);
    }
    return "UNSUBSCRIBE\nid:" + std::to_string(sId) + "\receipt:" + std::to_string(rId) + "\n\n";

} 

string StompProtocol::processReport(vector<string> vec)
{
    return "";
} 

string StompProtocol::processSummary(vector<string> vec)
{
    return "";
} 

string StompProtocol::processLogout(vector<string> vec, User &user)
{
    //assign rId
    //add in user map <rid, 'logout'>
    //parse frame
    int rId = user.assignRId();
    user.addReciept(rId, "logout successful");
    
    return "DISCONNECT\nreceipt: " + std::to_string(rId) + "\n\n";
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

int StompProtocol::getReciptId(std::string frame)
{
    vector<string> strComps = split(frame, '\n');
    if(strComps.at(0) == "RECEIPT") {
        return stoi(strComps.at(1).substr(11));
    }
    return -1;
}

bool StompProtocol::isErrorFrame(std::string frame)
{
    vector<string> strComps = split(frame, '\n');
    return strComps.at(0) == "ERROR";
}

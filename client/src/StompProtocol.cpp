#include "../include/StompProtocol.h"
#include "../include/event.h"
#include <queue>

using namespace std;

StompProtocol::StompProtocol() {}

std::queue<std::string> StompProtocol::createFrame(std::string command, User &user, GameTracker &gameTracker) 
{
    //we assume the command input is legal
    vector<string> strComps = split(command, ' ');
    string keyword = strComps.at(0);
    queue<string> outputQ;
    if(keyword == "login") 
    {
        outputQ.push(processLogin(strComps, user));
    } else if (keyword == "join")
    {
        outputQ.push(processJoin(strComps, user));
    } else if (keyword == "exit")
    {
        outputQ.push(processExit(strComps, user));
    } else if (keyword == "report")
    {
        outputQ = processReport(strComps, user);
    } else if (keyword == "summary")
    {
        processSummary(strComps, gameTracker);
    } else if (keyword == "logout")
    {
        outputQ.push(processLogout(strComps, user));
    } 

    return outputQ;
}

std::string StompProtocol::parseFrame(std::string frame, User &user, GameTracker &gameTracker)
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
    } else if (keyword == "MESSAGE") {
        output = frame;
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
    return "UNSUBSCRIBE\nid:" + std::to_string(sId) + "\nreceipt:" + std::to_string(rId) + "\n\n";

} 

queue<string> StompProtocol::processReport(vector<string> vec, User &user)
{
    // names_and_events nne = parseEventsFile(vec.at(vec.size() - 1));
    names_and_events nne = parseEventsFile("/home/spl211/Downloads/SPL3/SPL3_Networks/client/data/events1_partial.json");

    queue<string> output;
    for(Event e : nne.events)
    {
        //change time to minutes
        string frame = "SEND\ndestination:/" + e.get_team_a_name() + "_" + e.get_team_b_name() + "\n\nuser: " + user.getUserName() + "\nteam a: " + e.get_team_a_name() + "\nteam b: " + e.get_team_b_name() + "\nevent name: " + e.get_name() + "\ntime: " + std::to_string(e.get_time()) + "\ngeneral game updates:\n" + printfMap(e.get_game_updates()) + "\nteam a updates:\n" + printfMap(e.get_team_a_updates()) + "\nteam b updates:\n" + printfMap(e.get_team_b_updates()) + "\ndescription:\n" + e.get_discription() + "\n" ;
        output.push(frame);
    }

    return output;
} 

std::string StompProtocol::printfMap(const std::map<std::string, std::string> &map)
{
    string output = "";
    for(pair<string, string> key : map)
    {
        output += '\t' + key.first + ": " + key.second + "\n";
    }
    if(output.size() > 0) 
    {
        output.resize(output.size() - 1);
    }
    return output;
}


void StompProtocol::processSummary(vector<string> vec, GameTracker &gameTracker)
{
    //string summery = gametracker.createSummary(game, username)
    //write summery to given filename

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

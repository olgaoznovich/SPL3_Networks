#include "../include/Game.h"

Game::Game() : generalGameUpdates(), teamAUpdates(), teamBUpdates(), events()
{}

std::vector<std::string> Game::printfStatMaps() 
{
    std::vector<std::string> prints;
    prints.push_back(printfMap(generalGameUpdates));
    prints.push_back(printfMap(teamAUpdates));
    prints.push_back(printfMap(teamBUpdates));
    return prints;

}

std::string Game::printfMap(const boost::unordered_map<std::string,std::string> &map)
{
    std::string output = "";
    for(std::pair<std::string, std::string> key : map)
    {
        output += '\t' + key.first + ": " + key.second + "\n";
    }
    if(output.size() > 0) 
    {
        output.resize(output.size() - 1);
    }
    return output;
}

std::string Game::printEvents()
{
    std::string output = "";
    for(std::string event : events)
    {
        output += event + "\n";
    }
    return output;
}

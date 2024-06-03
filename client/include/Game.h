#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/container/vector.hpp>
#include <vector>


class Game 
{
    public:
        Game();
        Game(boost::unordered_map<std::string,std::string> generalStats, boost::unordered_map<std::string,std::string> teamAStats, boost::unordered_map<std::string,std::string> teamBStats);
        std::vector<std::string> printfStatMaps();
        std::string printEvents();
        void addEvent(std::string event);
        void updateAllStats(boost::unordered_map<std::string,std::string> generalStats, boost::unordered_map<std::string,std::string> teamAStats, boost::unordered_map<std::string,std::string> teamBStats);
    private:
        boost::unordered_map<std::string,std::string> generalGameUpdates;
        boost::unordered_map<std::string,std::string> teamAUpdates;
        boost::unordered_map<std::string,std::string> teamBUpdates;
        boost::container::vector<std::string> events;
        std::string printfMap(const boost::unordered_map<std::string,std::string> &map);
};
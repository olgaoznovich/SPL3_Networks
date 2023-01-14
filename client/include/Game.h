#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/container/vector.hpp>
#include <vector>


class Game 
{
    public:
        Game();
        std::vector<std::string> printfStatMaps();
        std::string printEvents();
    private:
        boost::unordered_map<std::string,std::string> generalGameUpdates;
        boost::unordered_map<std::string,std::string> teamAUpdates;
        boost::unordered_map<std::string,std::string> teamBUpdates;
        boost::container::vector<std::string> events;
        std::string printfMap(const boost::unordered_map<std::string,std::string> &map);
};
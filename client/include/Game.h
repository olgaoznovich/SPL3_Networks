#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/container/vector.hpp>



class Game 
{
    public:
        Game();
    private:
        boost::unordered_map<std::string,std::string> generalGameUpdates;
        boost::unordered_map<std::string,std::string> teamAUpdates;
        boost::unordered_map<std::string,std::string> teamBUpdates;
        boost::container::vector<std::string> events;
};
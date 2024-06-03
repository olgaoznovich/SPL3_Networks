#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include "../include/Game.h"

class GameTracker 
{
    public:
        GameTracker();
        std::string createSummary(std::string gameName, std::string username);
        void addGametoTracker(std::string gameName);
        void removeGameFromTracker(std::string gameName);
        void addUpdate(std::string username, std::string gameName, boost::unordered_map<std::string,std::string> generalStats, boost::unordered_map<std::string,std::string> teamAStats, boost::unordered_map<std::string,std::string> teamBStats, std::string event);
        void resetGameTracker();
    private:
        boost::unordered_map<std::string ,boost::unordered_map<std::string, Game>> tracker;

};
#pragma once

#include <string>
#include <boost/unordered_map.hpp>
#include "../include/Game.h"

class GameTracker 
{
    public:
        GameTracker();
    private:
        boost::unordered_map<std::string ,boost::unordered_map<std::string, Game>> tracker;

};
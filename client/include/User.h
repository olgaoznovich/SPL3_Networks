#pragma once

#include <string>
#include <boost/unordered_map.hpp>
class User
{
    private:
        int receiptIdCounter;
        int subIdCounter;
        std::string username;
        boost::unordered_map<int,std::string> receipts;
        boost::unordered_map<int,std::string> subsId2Game;
        boost::unordered_map<std::string, int> subsGame2Id;


    public:
        User();
        int assignRId();
        int assignSId();
        std::string getUserName();
        void setUserName(std::string newUsername);
        void addReciept(int recieptId, std::string frameType);
        std::string getReciept(int receiptId);
        void removeReciept(int receiptId);
        void addSubId2Game(int subId, std::string gameName);
        std::string getSubId2Game(int subId);
        void removeSubId2Game(int subId);
        void resetUser();
        void addSubGame2Id(std::string gameName, int subId);
        int getSubGame2Id(std::string gameName);
        void removeSubGame2Id(std::string gameName);

        
};
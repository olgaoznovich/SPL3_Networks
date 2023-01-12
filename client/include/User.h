#pragma once

#include <string>
#include <boost/unordered_map.hpp>
class User
{
    private:
        int receiptIdCounter;
        int subIdCounter;
        std::string username;
        boost::unordered_map<int,std::string> reciepts;
        boost::unordered_map<int,std::string> subs;

    public:
        User();
        int assignRId();
        int assignSId();
        std::string getUserName();
        void setUserName(std::string newUsername);
        void addReciept(int recieptId, std::string frameType);
        std::string getReciept(int receiptId);
        void removeReciept(int receiptId);
        void addSub(int subId, std::string gameName);
        std::string getSub(int subId);
        void removeSub(int subId);
        void resetUser();
};
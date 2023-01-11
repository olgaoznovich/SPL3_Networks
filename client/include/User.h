#pragma once

#include <string>
#include <boost/unordered_map.hpp>
class User
{
    private:
        int receiptIdCounter;
        std::string username;
        boost::unordered_map<int,std::string> reciepts;

    public:
        User();
        int assignRId();
        std::string getUserName();
        void setUserName(std::string newUsername);
        void addReciept(int recieptId, std::string frameType);
        std::string getReciept(int receiptId);
        void removeReciept(int receiptId);
        void resetUser();
};
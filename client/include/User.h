#pragma once

#include <string>

class User
{
    private:
        int receiptIdCounter;
        std::string username;
    public:
        User();
        int assignRId();
        std::string getUserName();
        void setUserName(std::string newUsername);
};
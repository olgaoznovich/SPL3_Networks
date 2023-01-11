#include "../include/ReadFromSocket.h"

ReadFromSocket::ReadFromSocket(ConnectionHandler &conHandler, StompProtocol &protocol, User &user) : conHandler(conHandler), protocol(protocol), shouldTerminate(false), user(user) 
{

}

void ReadFromSocket::Run()
{
    while(!shouldTerminate)
    {
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if(conHandler.getIsInit()) 
        {
            if (!conHandler.getLine(answer)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            
            //parse answer and return the reply according to it
            std::string replyToClient = protocol.parseFrame(answer, user);

            int rId = protocol.getReciptId(answer);
            if(rId != -1)
            {
                //check the type of the receipt in user
                //if "logout" - reset user, disconnect (handlerInit= false) from handler
                std::string frameType = user.getReciept(rId);
                if(frameType == "logout")
                {
                    user.resetUser();
                    conHandler.setIsInit(false);
                    std::cout << "disconnected user !!!!!!!!!!!" << std::endl;
                } else
                {
                    user.removeReciept(rId);
                }
            }
            int len=replyToClient.length();
            // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
            // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
            // if(len > 0)
            replyToClient.resize(len-1);
            std::cout << "Reply: " << replyToClient << " " << len << " bytes " << std::endl << std::endl;
            
        }
    }
}
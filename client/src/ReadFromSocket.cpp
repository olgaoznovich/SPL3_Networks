#include "../include/ReadFromSocket.h"

ReadFromSocket::ReadFromSocket(ConnectionHandler &conHandler, StompProtocol &protocol) : conHandler(conHandler), protocol(protocol), shouldTerminate(false) 
{

}

void ReadFromSocket::Run()
{
    while(!shouldTerminate)
    {
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!conHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        
        //parse answer and return the reply according to it
        answer = protocol.parseFrame(answer);

		int len=answer.length();
		// A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
		// we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        // if(len > 0)
        answer.resize(len-1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            
        }
    }
}
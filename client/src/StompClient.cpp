#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include "../include/ReadFromSocket.h"
#include "../include/StompProtocol.h"
#include <thread>

int main(int argc, char *argv[]) {
	ConnectionHandler connectionHandler("",0);
	StompProtocol protocol;
	ReadFromSocket socket(connectionHandler, protocol);
	std::thread socketThread(&ReadFromSocket::Run, &socket);

	//TODO: when disconnect command issued, set isInit to false again!!
	while(1)
    {
        std::cout << "enter command" << std::endl;
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
		std::string line(buf);
		int len=line.length();

        std::vector<std::string> hostAndPort = protocol.isLoginCommand(line);

        if(hostAndPort.size() > 0)
        {
            std::string host = hostAndPort.at(0);
            short port = stoi(hostAndPort.at(1));
            connectionHandler.setPort(port);
			connectionHandler.setHost(host);
			connectionHandler.setIsInit(true);
            if (!connectionHandler.connect()) {
                std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
				
            }                
        }
		
		if(connectionHandler.getIsInit()) {
			std::cout << "before createFrame" << std::endl;
			std::string frame = protocol.createFrame(line);
			//execute sendLine only!! if the command is correct and frame was built
			//for example if there was an error on client side, createframe will return "" and sendLIne wont be executed
			if (!connectionHandler.sendLine(frame)) {
				std::cout << "Disconnected. Exiting...\n" << std::endl;
				// shouldTerminate = true;
			}
			// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
			std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
		}
    }
	socketThread.join();

	return 0;
}
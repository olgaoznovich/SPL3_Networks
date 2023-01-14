#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include "../include/ReadFromSocket.h"
#include "../include/StompProtocol.h"
#include "../include/User.h"
#include "../include/GameTracker.h"
#include <thread>


#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[]) {
	ConnectionHandler connectionHandler("",0);
	StompProtocol protocol;
	User user;
	GameTracker gameTracker;
	ReadFromSocket socket(connectionHandler, protocol, user, gameTracker);
	std::thread socketThread(&ReadFromSocket::Run, &socket);
	

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current working dir: " << cwd << std::endl;
    } else {
        std::cout << "getcwd() error" << std::endl;
    }
    


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

        if(hostAndPort.size() > 0 && !connectionHandler.getIsInit())
        {
            std::string host = hostAndPort.at(0);
            short port = stoi(hostAndPort.at(1));
            connectionHandler.setPort(port);
			connectionHandler.setHost(host);
            if (!connectionHandler.connect()) {
                std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
				
            } else {
				connectionHandler.setIsInit(true);
			}               
        }

		if(connectionHandler.getIsInit()) {
			std::queue<std::string> frames = protocol.createFrame(line, user, gameTracker);
			//execute sendLine only!! if the command is correct and frame was built
			//for example if there was an error on client side, createframe will return "" and sendLIne wont be executed
			while(!frames.empty()) {
				std::string frame = frames.front();
				frames.pop();
				if (!connectionHandler.sendLine(frame)) {
					std::cout << "Disconnected. Exiting...\n" << std::endl;
				}
			}
			// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
		}
    }
	socketThread.join();

	return 0;
}
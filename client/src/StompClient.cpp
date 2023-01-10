#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include "../include/ReadFromKeyboard.h"
#include "../include/ReadFromSocket.h"
#include "../include/StompProtocol.h"
#include <thread>

int main(int argc, char *argv[]) {
	// TODO: implement the STOMP client

	// if (argc < 3) {
    //     std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
    //     return -1;
    // }
    // std::string host = argv[1];
    // short port = atoi(argv[2]);

	
	// std::string host = "stomp.cs.bgu.ac.il";
	std::string host = "127.0.0.1";
	short port = 7777;
    //host and port not neccessaricly constant so maybe they have to be midified after first login. LOOK INTO IT!
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

	StompProtocol protocol;
	ReadFromKeyboard keyboard(connectionHandler, protocol);
	ReadFromSocket socket(connectionHandler, protocol);

	std::thread keyboardThread(&ReadFromKeyboard::Run, &keyboard);
	std::thread socketThread(&ReadFromSocket::Run, &socket);

	keyboardThread.join();
	socketThread.join();

	return 0;
}
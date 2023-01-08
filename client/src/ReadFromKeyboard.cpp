#include "../include/ReadFromKeyboard.h"

ReadFromKeyboard::ReadFromKeyboard(ConnectionHandler &conHandler, StompProtocol &protocol) : conHandler(conHandler), shouldTerminate(false), protocol(protocol)
{

}

void ReadFromKeyboard::Run()
{
    while(!shouldTerminate)
    {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
		std::string line(buf);
		int len=line.length();
        //line = protocol.createFrame(line)
        std::string frame = protocol.createFrame(line);
        //execute sendLine only!! if the command is correct and frame was built
        //for example if there was an error on client side, createframe will return "" and sendLIne wont be executed
        if (!conHandler.sendLine(frame)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            // shouldTerminate = true;
        }
		// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
    }
}
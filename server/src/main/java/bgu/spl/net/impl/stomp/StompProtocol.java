package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.*;
import bgu.spl.net.srv.Connections;

public class StompProtocol implements StompMessagingProtocol<String> {
    private boolean shouldTerminate = false;

    public void start(int connectionId, Connections<String> connections) {
        //todo: implement
    }
    
    public String process(String message) {
        String[] msgComponents = message.split(System.lineSeparator());
        switch(msgComponents[0]) {
            case ("CONNECT"): {break;}
            case ("SEND"): {break;}
            case ("SUBSCRIBE"): {break;}
            case ("UNSUBSCRIBE"): {break;}
            case ("DISCONNECT"): {break;}
            default: 
        }
        return null;
    }

	
	/**
     * @return true if the connection should be terminated
     */
    public boolean shouldTerminate() {
        return shouldTerminate;
    }

}

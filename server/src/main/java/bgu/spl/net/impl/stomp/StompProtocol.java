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
        switch (msgComponents[0]) {
            case ("CONNECT") -> {
                System.out.println("CONNECT");
            }
            case ("DISCONNECT") -> {
                System.out.println("DISCONNECT");
            }
            case ("SEND") -> {
                System.out.println("SEND");
            }
            case ("SUBSCRIBE") -> {
                System.out.println("SUBSCRIBE");
            }
            case ("UNSUBSCRIBE") -> {
                System.out.println("UNSUBSCRIBE");
            }
            default -> {
                System.out.println("ERROR");
            }
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

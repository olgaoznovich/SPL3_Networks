package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.*;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class StompProtocol implements StompMessagingProtocol<String> {
    
    private boolean shouldTerminate = false;
    private int connectionId;
    private Connections<String> connections;
    private ConnectionHandler<String> handler;

    public void start(int connectionId, Connections<String> connections) {
        this.connectionId = connectionId;
        this.connections = connections;
    }
    
    public String process(String message) {
        String[] msgComponents = message.split(System.lineSeparator());
        String result = "";
        switch(msgComponents[0]) {
            case ("CONNECT"): {result = proccessConnect(msgComponents); break;}
            case ("SEND"): {result = proccessSend(msgComponents); break;}
            case ("SUBSCRIBE"): {result = proccessSubscribe(msgComponents); break;}
            case ("UNSUBSCRIBE"): {result = proccessUnsubscribe(msgComponents);  break;}
            case ("DISCONNECT"): {result = proccessDisconnect(msgComponents); break;}
            default: 
        }
        return result;
    }
    
    private String proccessConnect(String[] msgComps) {
        // recognize login header
        // Arrays.search

        // recognize password header


        return "";
    }

    private String proccessSend(String[] msgComps) {
        return "";
    }

    private String proccessSubscribe(String[] msgComps) {
        return "";
    }

    private String proccessUnsubscribe(String[] msgComps) {
        return "";
    }

    private String proccessDisconnect(String[] msgComps) {
        return "";
    }
	
	/**
     * @return true if the connection should be terminated
     */
    public boolean shouldTerminate() {
        return shouldTerminate;
    }

}

package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.*;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class StompProtocol implements StompMessagingProtocol<String> {
    private final int USERNAME_BEGIN_INDEX = 6;
    private final int PASSWORD_BEGIN_INDEX = 9;
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

        // recognize username header
        String username = null;
        for (String s: msgComps){
            if (s.contains("login")){
                username = s.substring(USERNAME_BEGIN_INDEX);
                break;
            }
        }
        // recognize password header
        String password = null;
        for (String s: msgComps){
            if (s.contains("password")){
                password = s.substring(PASSWORD_BEGIN_INDEX);
                break;
            }
        }
        if (username == null){

        }
        else if (password == null){

        }
        else {
            boolean succeed = connections.login(username, password, connectionId, handler);
            if (!succeed){

            }
        }
        // next thing add error messages and build answer...
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

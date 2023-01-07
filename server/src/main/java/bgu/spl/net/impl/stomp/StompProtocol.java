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

    private String[] msg;

    public void start(int connectionId, Connections<String> connections) {
        this.connectionId = connectionId;
        this.connections = connections;
    }
    
    public String process(String message) {
        String[] msgComponents = message.split(System.lineSeparator());
        this.msg = msgComponents;
        String result = "";
        switch(msgComponents[0]) {
            case ("CONNECT"): {result = proccessConnect(message); break;}
            case ("SEND"): {result = proccessSend(msgComponents); break;}
            case ("SUBSCRIBE"): {result = proccessSubscribe(msgComponents); break;}
            case ("UNSUBSCRIBE"): {result = proccessUnsubscribe(msgComponents);  break;}
            case ("DISCONNECT"): {result = proccessDisconnect(msgComponents); break;}
            default: 
        }
        return result;
    }
    
    private String proccessConnect(String message) {
        String errorMsg = "";
        // recognize username header
        String username = searchAndCut(USERNAME_BEGIN_INDEX, "login");
        
        // recognize password header
        String password = searchAndCut(PASSWORD_BEGIN_INDEX, "password");
        
        if (username == null){
            errorMsg += "Username is not valid";
        }
        else if (password == null){
            errorMsg += "Password must be filled";
        }
        else {
            boolean succeed = connections.login(username, password, connectionId, handler);
            if (!succeed){
                errorMsg += "Password incorrect";
            }
        }
        // next thing add error messages and build answer...

        String receipt = searchAndCut(8, "receipt");

        String output = "";
        if(errorMsg.equals("")) {
            output = "CONNECTED\nversion:1.2\n"+ receipt + "\n\u0000";
        } else {
            output = createErrorFrame("error with login", message, errorMsg);
        }

        return output;
    }

    private String searchAndCut(int subStart, String target) {
        String answer = null;
        for (String s: msg){
            if (s.contains(target)){
                answer = s.substring(subStart);
                break;
            }
        }
        return answer;
    }

    private String createErrorFrame(String message, String theMessage, String errExp) {
        //if recieptid is null then theres no recet header
        String recStr = checkRecipient();

        disconnect();

        return "ERROR" + recStr + "\nmessage:" + message +
            "\n\nThe message:\n-----\n" + theMessage +
            "\n-----\n" + errExp + "\n\u0000";
    }

    private String checkRecipient(){
        String recStr = searchAndCut(8, "receipt");
        if (recStr == null){
            return "";
        }
        else return "\nreciept-id:" + recStr;
    }


    private void disconnect(){
        connections.disconnect(connectionId);
        shouldTerminate = true;
    }

    private String proccessSend(String[] msgComps) {
        return "";
    }

    private String proccessSubscribe(String[] msgComps) {
        String topic = searchAndCut(13, "destination");
        String id = searchAndCut(3, "id");
        connections.subscribe(topic, connectionId, id);
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

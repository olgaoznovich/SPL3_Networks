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
            case ("CONNECT"): {result = proccessConnect(msgComponents, message); break;}
            case ("SEND"): {result = proccessSend(msgComponents); break;}
            case ("SUBSCRIBE"): {result = proccessSubscribe(msgComponents); break;}
            case ("UNSUBSCRIBE"): {result = proccessUnsubscribe(msgComponents);  break;}
            case ("DISCONNECT"): {result = proccessDisconnect(msgComponents); break;}
            default: 
        }
        return result;
    }
    
    private String proccessConnect(String[] msgComps, String message) {
        String errorMsg = "";
        // recognize username header
        String username = searchAndCut(msgComps, USERNAME_BEGIN_INDEX, "login");
        
        // recognize password header
        String password = searchAndCut(msgComps, PASSWORD_BEGIN_INDEX, "password");
        
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

        String receipt = searchAndCut(msgComps, 8, "receipt");

        String output = "";
        if(errorMsg.equals("")) {
            if(receipt == null)
                output = "CONNECTED\nversion:1.2\n\n\u0000";
            else
                output = "CONNECTED\nversion:1.2\n\nreciept-id:" + receipt + "\n\u0000";
        } else {
            output = createErrorFrame(receipt, "error with login", message, errorMsg);
        }

        return output;
    }

    private String searchAndCut(String[] msgComps, int subStart, String target) {
        String answer = null;
        for (String s: msgComps){
            if (s.contains(target)){
                answer = s.substring(subStart);
                break;
            }
        }
        return answer;
    }

    private String createErrorFrame(String receiptId, String message, String theMessage, String errExp) {
        //if recieptid is null then theres no recet header
        String recStr = "";
        if(receiptId != null) {
            recStr = "reciept-id:" + receiptId;
        }

        //disconnect

        return "ERROR\n" + recStr + "\nmessage:" + message + 
        "\n\nThe message:\n-----\n" + theMessage + 
        "\n-----\n" + errExp + "\n\u0000";
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

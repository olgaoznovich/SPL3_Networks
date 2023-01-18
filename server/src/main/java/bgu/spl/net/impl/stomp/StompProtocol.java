package bgu.spl.net.impl.stomp;

import java.util.HashSet;

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
    private String message;

    public void start(int connectionId, Connections<String> connections, ConnectionHandler<String> handler) {
        this.connectionId = connectionId;
        this.connections = connections;
        this.handler = handler;
    }
    
    public String process(String message) {
        String[] msgComponents = message.split(System.lineSeparator());
        this.msg = msgComponents;
        this.message = message;
        String result = "";
        switch(msgComponents[0]) {
            case ("CONNECT"): {result = proccessConnect(); break;}
            case ("SEND"): {result = proccessSend(); break;}
            case ("SUBSCRIBE"): {result = proccessSubscribe(); break;}
            case ("UNSUBSCRIBE"): {result = proccessUnsubscribe();  break;}
            case ("DISCONNECT"): {result = proccessDisconnect(); break;}
            default: 
        }
        return result;
    }
    
    private String proccessConnect() {
        String errorMsg = "";
        // recognize username header
        String username = searchAndCut(USERNAME_BEGIN_INDEX, "login");
        
        // recognize password header
        String password = searchAndCut(PASSWORD_BEGIN_INDEX, "passcode");
        
        if (username == null){
            errorMsg += "Username is not valid";
        }
        else if (password == null){
            errorMsg += "Password must be filled";
        }
        else {
            String loginErrorMsg = connections.login(username, password, connectionId, handler);
            if (loginErrorMsg.length() > 0){
                errorMsg += loginErrorMsg;
            }
        }
        // next thing add error messages and build answer...

        String receipt = checkRecipient();

        String output = "";
        if(errorMsg.equals("")) {
            //deleted null char bc encode (then send) adds it automatically
            // output = "CONNECTED\nversion:1.2\n"+ receipt + "\n" + '\u0000';
            output = "CONNECTED\nversion:1.2\n"+ receipt + "\n";

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

        if(!recStr.equals("")) {
            recStr = "\nreceipt:" + recStr;
        }

        return "ERROR" + recStr + "\nmessage:" + message +
            "\n\nThe message:\n-----\n" + theMessage +
            "\n-----\n" + errExp + "\n";
    }

    private String checkRecipient(){
        String recStr = searchAndCut(8, "receipt");
        if (recStr == null){
            return "";
        }
        else return recStr;
    }


    private void disconnect(){
        connections.disconnect(connectionId);
        shouldTerminate = true;
    }

    private String proccessSend() {
        int index = 0;
        for (int i = 0; i < msg.length; i++){
            if (msg[i].equals("")){
                index = i + 1;
                break;
            }
        }
        String topic = searchAndCut(13, "destination");
        String reportBody = "";
        for(int i = index; i < msg.length; i++) {
            if(i == msg.length - 1) {
                reportBody += msg[i];
            } else {
                reportBody += msg[i] + "\n";
            }
        }
        // connections.send(topic, reportBody);
        int msgID = connections.assignMsgId();
        String firstHalfFrame = "MESSAGE\nsubscription:";
        String secondHalfFrame = "\nmessage-id:" + msgID + "\ndestination:/" + topic + "\n\n" + reportBody + "\n";
    
        HashSet<Integer> topicSubs = connections.getTopicSubs(topic);
        for(int sub : topicSubs) {
            String output = firstHalfFrame + connections.getSubId(topic, sub) + secondHalfFrame;
            System.out.println(sub + ": " + output);
            connections.send(sub, output);
        }
        return null;
    }

    private String proccessSubscribe() {
        String topic = searchAndCut(13, "destination");
        String id = searchAndCut(3, "id");
        connections.subscribe(topic, connectionId, id);

        return createReceiptFrame();
    }

    private String proccessUnsubscribe() {
        String id = searchAndCut(3, "id");
        if(id.equals("-1")) {
            return createErrorFrame("error with unsubscribe", message, "user wasn't subscribed to that channel");
        }
        connections.unsubscribe(connectionId, id);
        return createReceiptFrame();
    }

    private String proccessDisconnect() {
        connections.disconnect(connectionId);
        return createReceiptFrame();
    }

    private String createReceiptFrame() {
        String rId = checkRecipient();
        return "RECEIPT\nreceipt-id:" + rId + "\n\n";
    }
	
	/**
     * @return true if the connection should be terminated
     */
    public boolean shouldTerminate() {
        return shouldTerminate;
    }

}

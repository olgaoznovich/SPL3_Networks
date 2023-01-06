package bgu.spl.net.srv;

import java.util.HashMap;
import java.util.HashSet;
import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl implements Connections<String> {

    private int idCounter;
    private ConcurrentHashMap<Integer, ConnectionHandler<String>> connectedUsers;
    private ConcurrentHashMap<String, String> registeredUsers;

    public ConnectionsImpl() {
        idCounter = 0;
        connectedUsers = new ConcurrentHashMap<>();
        registeredUsers = new ConcurrentHashMap<>();
    }

    public boolean send(int connectionId, String msg){ 
        //todo: implement
        return false;
    }

    public void send(String channel, String msg) {
        //todo: implement
    }

    public void disconnect(int connectionId) { 
        //todo: implement
    }

    public boolean login(String username, String password, int connectionId, ConnectionHandler<String> handler) {
        if(registeredUsers.containsKey(username)) {
            if(!password.equals(registeredUsers.get(username))) {
                return false;
            }
        } else {
            registeredUsers.put(username, password);
        }
        connectedUsers.put(connectionId, handler); // todo: return
        return true;
    }

    public int assignId() {
        return idCounter++;
    }


}

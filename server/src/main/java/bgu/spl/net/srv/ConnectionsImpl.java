package bgu.spl.net.srv;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.concurrent.ConcurrentHashMap;


public class ConnectionsImpl implements Connections<String> {

    private int idCounter;
    private ConcurrentHashMap<Integer, ConnectionHandler<String>> connectedUsers;
    private ConcurrentHashMap<String, String> registeredUsers;
    private ConcurrentHashMap<String, HashSet<Integer>> topicSubs; //<topic, Set<connectionId>>
    private ConcurrentHashMap<String, ConcurrentHashMap<Integer, Integer>> topicToId;  //<topic, cId, id>
    private ConcurrentHashMap<Integer, ConcurrentHashMap<Integer, String>> idToTopic; //<id, cId, topic>

    public ConnectionsImpl() {
        idCounter = 0;
        connectedUsers = new ConcurrentHashMap<>();
        registeredUsers = new ConcurrentHashMap<>();
        topicSubs = new ConcurrentHashMap<>();
        topicToId = new ConcurrentHashMap<>();
        idToTopic = new ConcurrentHashMap<>();
    }

    public boolean send(int connectionId, String msg){ 
        //todo: implement
        return false;
    }

    public void send(String channel, String msg) {
        //todo: implement
    }

    public void disconnect(int connectionId) {
        for(ConcurrentHashMap<Integer, Integer> s : topicToId.values()) {
            s.remove(connectionId);
        }
        connectedUsers.remove(connectionId);
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

    @Override
    public void subscribe(String topic, int connectionId, String id) {
        Integer idInt = Integer.parseInt(id);
        ConcurrentHashMap<Integer, String> ciDtoTopic = idToTopic.get(id);
        if (ciDtoTopic == null){
            ciDtoTopic = new ConcurrentHashMap<>();
        }

        topicToId.get(connectionId).put(connectionId, idInt);
        idToTopic.get(id).put(connectionId, topic);
    }

    public int assignId() {
        return idCounter++;
    }
}

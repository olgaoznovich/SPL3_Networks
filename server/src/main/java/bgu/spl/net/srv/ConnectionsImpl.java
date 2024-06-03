package bgu.spl.net.srv;

import bgu.spl.net.impl.stomp.IdConnectionId;
import bgu.spl.net.impl.stomp.TopicConnectionId;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentHashMap;


public class ConnectionsImpl<T> implements Connections<T> {

    private int idCounter;
    private int msgIdCounter;
    private ConcurrentHashMap<String, Integer> usernameToConId;
    private ConcurrentHashMap<Integer, ConnectionHandler<T>> connectedUsers;
    private ConcurrentHashMap<String, String> registeredUsers;
    private ConcurrentHashMap<String, HashSet<Integer>> topicSubs; //<topic, Set<connectionId>>
    private ConcurrentHashMap<TopicConnectionId, Integer> topicToId;
    private ConcurrentHashMap<IdConnectionId, String> idToTopic;
    public ConnectionsImpl() {
        idCounter = 0;
        msgIdCounter = 0;
        connectedUsers = new ConcurrentHashMap<>();
        registeredUsers = new ConcurrentHashMap<>();
        topicSubs = new ConcurrentHashMap<>();
        topicToId = new ConcurrentHashMap<>();
        idToTopic = new ConcurrentHashMap<>();
        usernameToConId = new ConcurrentHashMap<>();
    }

    public boolean send(int connectionId, T msg){ 
        connectedUsers.get(connectionId).send(msg);
        return false;
    }

    public void send(String channel, T msg) {
        //todo: implement
        HashSet<Integer> subbs = topicSubs.get(channel);
        for (Integer sub : subbs){
            send(sub, msg);
        }
    }

    public HashSet<Integer> getTopicSubs(String topic) {
        return topicSubs.get(topic);
    }

    public int getSubId(String topic, int conId) {
        return topicToId.get(new TopicConnectionId(topic, conId));
    }


    public void disconnect(int connectionId) {
        for (TopicConnectionId s : topicToId.keySet()){
            if (s.getConnectionID() == connectionId){
                topicToId.remove(s);
            }
        }

        for (IdConnectionId s : idToTopic.keySet()){
            if(s.getConnectionId() == connectionId){
                idToTopic.remove(s);
            }
        }

        for (String s : topicSubs.keySet()){
            if (topicSubs.get(s).contains(connectionId)){
                topicSubs.get(s).remove(connectionId);
            }
        }

        for (String username : usernameToConId.keySet()){
            if (usernameToConId.get(username) == connectionId){
                usernameToConId.remove(username);
            }
        }

        connectedUsers.remove(connectionId);
    }

    public String login(String username, String password, int connectionId, ConnectionHandler<T> handler) {
        if(registeredUsers.containsKey(username)) {
            if(usernameToConId.containsKey(username))
                return "User already logged in";
            
            if(!password.equals(registeredUsers.get(username))) {
                return "Wrong password";
            }
        } else {
            registeredUsers.put(username, password);
        }
        connectedUsers.put(connectionId, handler); // todo: return
        usernameToConId.put(username,connectionId);
        return "";
    }

    @Override
    public void subscribe(String topic, int connectionId, String id) {
        int idInt = Integer.parseInt(id);
        idToTopic.put(new IdConnectionId(idInt, connectionId), topic);
        topicToId.put(new TopicConnectionId(topic, connectionId), idInt);
        if (!topicSubs.containsKey(topic)){
            HashSet<Integer> connections = new HashSet<>();
            topicSubs.put(topic, connections);
        }
        topicSubs.get(topic).add(connectionId);

    }

    @Override
    public void unsubscribe(int connectionId, String id) {
        int idInt = Integer.parseInt(id);
        IdConnectionId idConnectionId = new IdConnectionId(idInt, connectionId);

        String topic = idToTopic.get(idConnectionId);
        TopicConnectionId topicConnectionId = new TopicConnectionId(topic, connectionId);

        idToTopic.remove(idConnectionId);
        topicToId.remove(topicConnectionId);

        topicSubs.get(topic).remove(connectionId);
    }

    public int assignId() {
        return idCounter++;
    }

    public int assignMsgId() {
        return msgIdCounter++;
    }

}

package bgu.spl.net.srv;

import bgu.spl.net.impl.stomp.IdConnectionId;
import bgu.spl.net.impl.stomp.TopicConnectionId;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;


public class ConnectionsImpl<T> implements Connections<T> {

    private AtomicInteger idCounter;
    private ConcurrentHashMap<Integer, ConnectionHandler<T>> connectedUsers;
    private ConcurrentHashMap<String, String> registeredUsers;
    private ConcurrentHashMap<String, HashSet<Integer>> topicSubs; //<topic, Set<connectionId>>
    private ConcurrentHashMap<TopicConnectionId, Integer> topicToId;
    private ConcurrentHashMap<IdConnectionId, String> idToTopic;
    public ConnectionsImpl() {
        AtomicInteger idCounter = new AtomicInteger(0);
        connectedUsers = new ConcurrentHashMap<>();
        registeredUsers = new ConcurrentHashMap<>();
        topicSubs = new ConcurrentHashMap<>();
        topicToId = new ConcurrentHashMap<>();
        idToTopic = new ConcurrentHashMap<>();
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

    public void disconnect(int connectionId) {
        for (TopicConnectionId s : topicToId.keySet()){
            if (s.getConnectionID() == connectionId){
                topicToId.remove(s);
            }
        }
        connectedUsers.remove(connectionId);
    }

    public boolean login(String username, String password, int connectionId, ConnectionHandler<T> handler) {
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
        return idCounter.getAndIncrement();
    }
}

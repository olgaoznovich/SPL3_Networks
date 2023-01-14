package bgu.spl.net.srv;

import java.io.IOException;
import java.util.HashSet;

public interface Connections<T> {

    boolean send(int connectionId, T msg);

    void send(String channel, T msg);

    void disconnect(int connectionId);

    boolean login(String username, String password, int connectionId, ConnectionHandler<T> handler );

    void subscribe(String topic, int connectionId, String id);

    void unsubscribe(int connectionId, String id);

    int assignId();

    int assignMsgId();

    HashSet<Integer> getTopicSubs(String topic);

    int getSubId(String topic, int conId);
}

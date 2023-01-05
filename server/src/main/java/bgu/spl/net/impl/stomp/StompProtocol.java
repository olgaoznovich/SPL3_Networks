package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.*;
import bgu.spl.net.srv.Connections;

public class StompProtocol<T> implements StompMessagingProtocol<T> {


    public void start(int connectionId, Connections<T> connections) {
        //todo: implement
    }
    
    public T process(T message) {
        //todo: implement
        return null;
    }
	
	/**
     * @return true if the connection should be terminated
     */
    public boolean shouldTerminate() {
        //todo: implement
        return true;
    }

}

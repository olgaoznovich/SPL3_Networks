package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.StompMessagingProtocol;

import java.util.function.Supplier;

public class ServerFactory<T> {
    private int port;
    private int numThreads;
    private Supplier<StompMessagingProtocol<T>> protocolFactory;
    private Supplier<MessageEncoderDecoder<T>> readerFactory;
    private boolean bool;
    public ServerFactory(
            int numThreads,
            int port,
            Supplier<StompMessagingProtocol<T>> protocolFactory,
            Supplier<MessageEncoderDecoder<T>> readerFactory,
            boolean bool){
        this.port = port;
        this.numThreads = numThreads;
        this.protocolFactory = protocolFactory;
        this.readerFactory = readerFactory;
        this.bool = bool;
    }

    public Server<T> getServer(){
        if (bool) return new Reactor<>(numThreads, port, protocolFactory, readerFactory);
        else return Server.threadPerClient(port,protocolFactory, readerFactory);
    }

}

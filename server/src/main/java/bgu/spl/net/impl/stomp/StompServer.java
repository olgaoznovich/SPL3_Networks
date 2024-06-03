package bgu.spl.net.impl.stomp;

import bgu.spl.net.impl.stomp.StompProtocol;
import bgu.spl.net.impl.echo.LineMessageEncoderDecoder;
import bgu.spl.net.srv.Server;
import bgu.spl.net.srv.ServerFactory;

public class StompServer {

    public static void main(String[] args) {
        int port = Integer.parseInt(args[0]);
        String serverType = args[1];
        boolean isReactor = args[1].equals("reactor");
        int numberOfThreads = 3;
        ServerFactory<String> stringServerFactory = new ServerFactory<>(numberOfThreads,
                port,
                StompProtocol::new,
                LineMessageEncoderDecoder::new,
                isReactor);
        Server<String> server = stringServerFactory.getServer();
        server.serve();

    }
}

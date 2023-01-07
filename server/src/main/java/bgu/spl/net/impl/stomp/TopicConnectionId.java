package bgu.spl.net.impl.stomp;

public class TopicConnectionId {
    private final String topic;
    private final int connectionID;


    public TopicConnectionId(String topic, int connectionID) {
        this.topic = topic;
        this.connectionID = connectionID;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        TopicConnectionId that = (TopicConnectionId) o;

        if (connectionID != that.connectionID) return false;
        return topic.equals(that.topic);
    }

    @Override
    public int hashCode() {
        int result = topic.hashCode();
        result = 31 * result + connectionID;
        return result;
    }

    public String getTopic() {
        return topic;
    }

    public int getConnectionID() {
        return connectionID;
    }
}

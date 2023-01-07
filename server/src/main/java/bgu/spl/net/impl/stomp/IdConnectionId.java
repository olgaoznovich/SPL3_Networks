package bgu.spl.net.impl.stomp;

public class IdConnectionId {
    private final int id;
    private final int connectionId;

    public IdConnectionId(int id, int connectionId) {
        this.id = id;
        this.connectionId = connectionId;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        IdConnectionId that = (IdConnectionId) o;

        if (id != that.id) return false;
        return connectionId == that.connectionId;
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + connectionId;
        return result;
    }

    public int getId() {
        return id;
    }

    public int getConnectionId() {
        return connectionId;
    }
}

package java.mc;

public abstract class MicroApplication {

    protected MicroApplication() {}

    public abstract void main() throws MicroApplicationException;;

    public abstract void onLoad(byte[] data, short offset, short length)
            throws MicroApplicationException;

    public native void sleep(short milliseconds);

}

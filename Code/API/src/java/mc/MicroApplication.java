package java.mc;

public abstract class MicroApplication {

    protected MicroApplication() {}

    public abstract void main();

    public abstract void onLoad(byte[] data, short offset, short length);

    public static native void Sleep(short milliseconds);

}

package java.mc;

public abstract class MicroApplication {

    protected MicroApplication() {}

    public abstract void main();

    public static native void ClearEvent(byte event);

    public static native void SetEvent(byte event);

    public static native void Sleep(short milliseconds);

}

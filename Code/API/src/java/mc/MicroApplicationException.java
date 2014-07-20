package java.mc;

public class MicroApplicationException extends Exception {

    public static final short UNAVAILABLE_FUNCTIONALITY = (short) 0;

    public MicroApplicationException(short reason) {}

    public native static void throwIt(short reason);

    public native static void setReason(short reason);

    public native static short getReason();

}

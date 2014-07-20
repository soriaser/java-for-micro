package java.mc.timers;

import java.mc.MicroApplicationException;

public final class Timer {

    public native static Timer getTimer(byte timer)
            throws MicroApplicationException;

    public native void clear();

    public native void disable();

    public native void enable();

    public native void read();

    public native void write(short timer);

}

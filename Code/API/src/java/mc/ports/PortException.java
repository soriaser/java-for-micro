package java.mc.ports;

import java.mc.MicroApplicationException;

public class PortException extends MicroApplicationException {

    public static short UNAVAILABLE_PIN = (short) 0;

    public static short UNAVAILABLE_PORT = (short) 1;

    public static short UNAVAILABLE_EVENT = (short) 2;

    public PortException(short reason) {
        super(reason);
    }

}

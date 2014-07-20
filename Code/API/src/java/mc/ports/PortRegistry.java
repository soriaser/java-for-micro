package java.mc.ports;

import java.mc.MicroApplicationException;


public final class PortRegistry {

    public native static PortRegistry getPortRegistry(byte port)
            throws MicroApplicationException;

    public native void setEvent(byte event) throws PortException;

    public native void clearEvent(byte event) throws PortException;

    public native void setPinToZero(byte pin) throws PortException;

    public native void setPinToOne(byte pin) throws PortException;

    public native void setPins(byte pins) throws PortException;

    public native void setInputPin(byte pin) throws PortException;

    public native void setOuputPin(byte pin) throws PortException;

    public native void setIO(byte directions) throws PortException;

}

package java.mc.ports;


public final class PortRegistry {

    public native static PortRegistry getPortRegistry(byte port);

    public native void setEvent(byte event);

    public native void clearEvent(byte event);

    public native void setPinToZero(byte pin);

    public native void setPinToOne(byte pin);

    public native void setPins(byte pins);

    public native void setInputPin(byte pin);

    public native void setOuputPin(byte pin);

    public native void setIO(byte directions);

}

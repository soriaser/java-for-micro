package jmc.converter;

public interface JCReducedConstants {

    public static final String API_METHOD_CLEAREVENT = "ClearEvent";
    public static final String API_METHOD_CLINIT = "<clinit>";
    public static final String API_METHOD_GETPORT = "getPort";
    public static final String API_METHOD_INIT = "<init>";
    public static final String API_METHOD_MAIN = "main";
    public static final String API_METHOD_ONEVENT = "onEvent";
    public static final String API_METHOD_RECEIVE = "Receive";
    public static final String API_METHOD_SEND = "Send";
    public static final String API_METHOD_SETEVENT = "SetEvent";
    public static final String API_METHOD_SETINPUTPIN = "setInputPin";
    public static final String API_METHOD_SETOUTPUTPIN = "setOutputPin";
    public static final String API_METHOD_SETPINTOONE = "setPinToOne";
    public static final String API_METHOD_SETPINTOZERO = "setPinToZero";
    public static final String API_METHOD_SLEEP = "Sleep";
    public static final String API_PACKAGE_MICROAPPLICATION = "java.mc.MicroApplication";
    public static final String API_PACKAGE_OBJECT = "java.lang.Object";
    public static final String API_PACKAGE_PORT= "java.mc.ports.Port";
    public static final String API_PACKAGE_SERIALPORT= "java.mc.serialport.SerialPort";

    public static final byte BIT_MASK_NATIVE = (byte) 0x80;

    public static final byte ID_METHOD_MICROAPPLICATION_INIT            = (byte) (BIT_MASK_NATIVE | 0x00);
    public static final byte ID_METHOD_MICROAPPLICATION_CLEAREVENT      = (byte) (BIT_MASK_NATIVE | 0x01);
    public static final byte ID_METHOD_MICROAPPLICATION_SETEVENT        = (byte) (BIT_MASK_NATIVE | 0x02);
    public static final byte ID_METHOD_MICROAPPLICATION_SLEEP           = (byte) (BIT_MASK_NATIVE | 0x03);
    public static final byte ID_METHOD_PORTREGISTRY_GETPORT             = (byte) (BIT_MASK_NATIVE | 0x04);
    public static final byte ID_METHOD_PORTREGISTRY_SETPINTOZERO        = (byte) (BIT_MASK_NATIVE | 0x05);
    public static final byte ID_METHOD_PORTREGISTRY_SETPINTOONE         = (byte) (BIT_MASK_NATIVE | 0x06);
    public static final byte ID_METHOD_PORTREGISTRY_SETINPUTPIN         = (byte) (BIT_MASK_NATIVE | 0x07);
    public static final byte ID_METHOD_PORTREGISTRY_SETOUTPUTPIN        = (byte) (BIT_MASK_NATIVE | 0x08);
    public static final byte ID_METHOD_SERIALPORT_RECEIVE               = (byte) (BIT_MASK_NATIVE | 0x09);
    public static final byte ID_METHOD_SERIALPORT_SEND                  = (byte) (BIT_MASK_NATIVE | 0x0A);
}

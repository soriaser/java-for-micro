package jmc.converter;

public interface JCReducedConstants {

    public static final String API_METHOD_GETPORTREGISTRY = "getPortRegistry";
    public static final String API_METHOD_INIT = "<init>";
    public static final String API_METHOD_MAIN = "main";
    public static final String API_METHOD_ONLOAD = "onLoad";
    public static final String API_METHOD_SETINPUTPIN = "setInputPin";
    public static final String API_METHOD_SETOUTPUTPIN = "setOutputPin";
    public static final String API_METHOD_SETPINTOONE = "setPinToOne";
    public static final String API_METHOD_SETPINTOZERO = "setPinToZero";
    public static final String API_METHOD_SLEEP = "Sleep";
    public static final String API_PACKAGE_MICROAPPLICATION = "java.mc.MicroApplication";
    public static final String API_PACKAGE_OBJECT = "java.lang.Object";
    public static final String API_PACKAGE_PORTREGISTRY = "java.mc.ports.PortRegistry";

    public static final byte BIT_MASK_NATIVE = (byte) 0x80;

    public static final byte ID_METHOD_MICROAPPLICATION_INIT            = (byte) (BIT_MASK_NATIVE | 0x00);
    public static final byte ID_METHOD_MICROAPPLICATION_MAIN            = (byte) (BIT_MASK_NATIVE | 0x01);
    public static final byte ID_METHOD_MICROAPPLICATION_SLEEP           = (byte) (BIT_MASK_NATIVE | 0x02);
    public static final byte ID_METHOD_PORTREGISTRY_GETPORTREGISTRY     = (byte) (BIT_MASK_NATIVE | 0x03);
    public static final byte ID_METHOD_PORTREGISTRY_SETPINTOZERO        = (byte) (BIT_MASK_NATIVE | 0x06);
    public static final byte ID_METHOD_PORTREGISTRY_SETPINTOONE         = (byte) (BIT_MASK_NATIVE | 0x07);
    public static final byte ID_METHOD_PORTREGISTRY_SETINPUTPIN         = (byte) (BIT_MASK_NATIVE | 0x09);
    public static final byte ID_METHOD_PORTREGISTRY_SETOUTPUTPIN        = (byte) (BIT_MASK_NATIVE | 0x0A);
}

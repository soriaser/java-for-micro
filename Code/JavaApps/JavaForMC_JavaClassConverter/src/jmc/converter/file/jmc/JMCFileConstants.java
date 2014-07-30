package jmc.converter.file.jmc;

public interface JMCFileConstants {
    public final static byte VERSION_MSB = (byte) 0x00;
    public final static byte VERSION_LSB = (byte) 0x01;
    public final static byte TAG_CLASS = (byte) 0x80;
    public final static byte TAG_FIELDS = (byte) 0x81;
    public final static byte TAG_METHODS = (byte) 0x81;
    public final static byte TAG_FIELD = (byte) 0xC1;
    public final static byte TAG_METHOD = (byte) 0xC2;
}

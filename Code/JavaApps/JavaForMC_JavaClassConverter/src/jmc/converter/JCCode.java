package jmc.converter;

import jmc.converter.util.Util;

public class JCCode {

    private int offset;

    private byte[] code;

    public JCCode(int size) {
        this.code = new byte[size];
        this.offset = 0;
    }

    public void appendArray(byte array[]) {
        for (int ii = 0; ii < array.length; ii++) {
            this.appendByte(array[ii]);
        }
    }

    public void appendByte(byte value) {
        this.code[offset] = value;
        this.offset++;
    }

    public void appendShort(short value) {
        if (JCConverter.isLittleEndian) {
            value = Util.revert(value);
        }

        this.appendByte((byte) (value >> 8));
        this.appendByte((byte) (value >> 0));
    }

    public void appendInt(int value) {
        if (JCConverter.isLittleEndian) {
            value = Util.revert(value);
        }

        this.appendByte((byte) (value >> 24));
        this.appendByte((byte) (value >> 16));
        this.appendByte((byte) (value >>  8));
        this.appendByte((byte) (value >>  0));        
    }

    public byte[] getCode() {
        return this.code;
    }

    public int getSize() {
        return this.code.length;
    }

}

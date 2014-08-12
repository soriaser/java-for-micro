package jmc.converter.file.jmc;

import jmc.converter.util.Util;

public abstract class JMCFileTLV {

    protected byte tag;

    protected byte lengthSize;

    public JMCFileTLV() {}

    public byte getTag() {
        return this.tag;
    }

    public abstract int getLength();

    public abstract String getValue();

    public String getTLV() {
        String tlv = "";

        tlv += Util.byte2HexString(this.tag);

        for (int ii = this.lengthSize; ii > 0; ii--) {
            tlv += Util.byte2HexString((byte) (getLength() >> ((ii - 1) * 8)));            
        }

        tlv += getValue();

        return tlv;
    }
}

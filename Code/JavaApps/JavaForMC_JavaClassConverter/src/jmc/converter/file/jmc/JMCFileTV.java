package jmc.converter.file.jmc;

import jmc.converter.util.Util;

public abstract class JMCFileTV {

    protected byte tag;

    public JMCFileTV() {}

    public byte getTag() {
        return this.tag;
    }

    public abstract String getValue();

    public String getTV() {
        String tlv = "";

        tlv += Util.byte2HexString(this.tag);
        tlv += getValue();

        return tlv;
    }
}

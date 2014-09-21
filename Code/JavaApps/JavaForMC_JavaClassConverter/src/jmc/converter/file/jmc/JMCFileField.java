package jmc.converter.file.jmc;

import jmc.converter.util.Util;

public class JMCFileField extends JMCFileTV {

    private byte id;

    public JMCFileField(byte id) {
        this.tag = JMCFileConstants.TAG_FIELD;
        this.id = id;
    }

    public JMCFileField(JMCFileField field) {
        this.tag = field.getTag();
        this.id = field.getID();
    }

    public byte getID() {
        return this.id;
    }

    public void setID(byte id) {
        this.id = id;
    }

    @Override
    public String getValue() {
        return Util.byte2HexString(this.id);
    }
}

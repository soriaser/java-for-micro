package jmc.converter.file.jmc;

import jmc.converter.util.Util;

public class JMCFileField extends JMCFileTLV {

    private byte id;
    
    public final static int LENGTH_SIZE = 1;

    public JMCFileField(byte id) {
        this.tag = JMCFileConstants.TAG_FIELD;
        this.id = id;
        this.lengthSize = LENGTH_SIZE;
    }

    public JMCFileField(JMCFileField field) {
        this.tag = field.getTag();
        this.id = field.getID();
        this.lengthSize = LENGTH_SIZE;
    }

    public byte getID() {
        return this.id;
    }

    public void setID(byte id) {
        this.id = id;
    }

    @Override
    public int getLength() {
        return 1; // 1 ID byte
    }

    @Override
    public String getValue() {
        return Util.byte2HexString(this.id);
    }
}

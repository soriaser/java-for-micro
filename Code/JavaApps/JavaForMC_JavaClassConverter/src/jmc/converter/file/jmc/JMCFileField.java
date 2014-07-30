package jmc.converter.file.jmc;

public class JMCFileField extends JMCFileTLV {

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
}

package jmc.converter;

public class JCReducedClass {

    public final static byte SIZE = 2;

    private byte id = 0;

    private byte superclass = (byte) 0xFF;

    private byte fields = (byte) 0xFF;

    private boolean isMain = false;

    public JCReducedClass(byte id) {
        this.id = id;
    }

    public JCReducedClass(byte id, byte superclass, byte fields) {
        this.id = id;
        this.superclass = superclass;
        this.fields = fields;
    }

    public byte getFields() {
        return this.fields;
    }

    public byte getId() {
        return this.id;
    }

    public byte getSuperClass() {
        return this.superclass;
    }

    public boolean isMain() {
        return this.isMain;
    }

    public void setStaticFields(byte fields) {
        this.fields = fields;
    }

    public void setId(byte id) {
        this.id = id;
    }

    public void setAsMain(boolean isMain) {
        this.isMain = isMain;
    }

    public void setSuperClass(byte superclass) {
        this.superclass = superclass;
    }

}

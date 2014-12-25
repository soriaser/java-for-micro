package jmc.converter;

public class JCFieldOrMethod {

    protected String name;

    protected String namePackage;

    protected String type;

    protected short index;

    protected byte id;

    protected byte idClass;

    public JCFieldOrMethod(String name, String namePackage, String type, short index,
            byte id, byte idClass) {
        this.name = name;
        this.namePackage = namePackage;
        this.type = type;
        this.index = index;
        this.id = id;
        this.idClass = idClass;

        this.setId();
    }

    public byte getID() {
        return this.id;
    }

    public byte getIDClass() {
        return this.idClass;
    }

    public short getIndex() {
        return this.index;
    }

    public String getName() {
        return this.name;
    }

    public String getNamePackage() {
        return this.namePackage;
    }

    public String getType() {
        return this.type;
    }

    protected void setId() {}

}

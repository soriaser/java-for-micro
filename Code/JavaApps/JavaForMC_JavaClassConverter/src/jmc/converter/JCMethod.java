package jmc.converter;

public class JCMethod {

    private String name;

    private String namePackage;

    private String type;

    private short index;

    private byte id;

    private byte idClass;

    public JCMethod(String name, String namePackage, String type, short index,
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

    private void setId() {
        if (namePackage.equals(JCReducedConstants.API_PACKAGE_MICROAPPLICATION)) {
            if (name.equals(JCReducedConstants.API_METHOD_INIT)) {
                if (type.equals("()V")) {
                    this.id = JCReducedConstants.ID_METHOD_MICROAPPLICATION_INIT;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_MAIN)) {
                if (type.equals("()V")) {
                    this.id = JCReducedConstants.ID_METHOD_MICROAPPLICATION_MAIN;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SLEEP)) {
                if (type.equals("(S)V")) {
                    this.id = JCReducedConstants.ID_METHOD_MICROAPPLICATION_SLEEP;
                }
            }
        } else if (namePackage.equals(JCReducedConstants.API_PACKAGE_PORTREGISTRY)) {
            if (name.equals(JCReducedConstants.API_METHOD_GETPORTREGISTRY)) {
                if (type.equals("(B)Ljava/mc/ports/PortRegistry;")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_GETPORTREGISTRY;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETPINTOZERO)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETPINTOZERO;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETPINTOONE)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETPINTOONE;
                }
            }
        }
    }
}

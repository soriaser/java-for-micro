package jmc.converter;

public class JCField extends JCFieldOrMethod {

    public JCField(String name, String namePackage, String type, short index, byte id, byte idClass) {
        super(name, namePackage, type, index, id, idClass);
        this.setId();
    }

    protected void setId() {
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

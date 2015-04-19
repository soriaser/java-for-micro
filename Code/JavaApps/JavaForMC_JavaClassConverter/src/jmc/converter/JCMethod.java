package jmc.converter;

public class JCMethod extends JCFieldOrMethod {

    public JCMethod(String name, String namePackage, String type, short index,
            byte id, byte idClass) {
        super(name, namePackage, type, index, id, idClass);
        this.setId();
    }

    protected void setId() {
        if (namePackage.equals(JCReducedConstants.API_PACKAGE_MICROAPPLICATION)) {
            if (name.equals(JCReducedConstants.API_METHOD_INIT)) {
                if (type.equals("()V")) {
                    this.id = JCReducedConstants.ID_METHOD_MICROAPPLICATION_INIT;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SLEEP)) {
                if (type.equals("(S)V")) {
                    this.id = JCReducedConstants.ID_METHOD_MICROAPPLICATION_SLEEP;
                }
            }
        } else if (namePackage.equals(JCReducedConstants.API_PACKAGE_PORT)) {
            if (name.equals(JCReducedConstants.API_METHOD_GETPORT)) {
                if (type.equals("(B)Ljava/mc/ports/Port;")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_GETPORT;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETEVENT)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETEVENT;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETPINTOZERO)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETPINTOZERO;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETPINTOONE)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETPINTOONE;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETINPUTPIN)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETINPUTPIN;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETOUTPUTPIN)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETOUTPUTPIN;
                }
            }
        } else if (namePackage.equals(JCReducedConstants.API_PACKAGE_SERIALPORT)) {
            if (name.equals(JCReducedConstants.API_METHOD_GETSERIALPORT)) {
                if (type.equals("()Ljava/mc/serialport/SerialPort;")) {
                    this.id = JCReducedConstants.ID_METHOD_SERIALPORT_GETSERIALPORT;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SEND)) {
                if (type.equals("([BSS)V")) {
                    this.id = JCReducedConstants.ID_METHOD_SERIALPORT_SEND;
                }
            }
        }
    }

}

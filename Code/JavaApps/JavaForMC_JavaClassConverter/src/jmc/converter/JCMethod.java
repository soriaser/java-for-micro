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
            } else if (name.equals(JCReducedConstants.API_METHOD_SETEVENT)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_MICROAPPLICATION_SETEVENT;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_CLEAREVENT)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_MICROAPPLICATION_CLEAREVENT;
                }
            }
        } else if (namePackage.equals(JCReducedConstants.API_PACKAGE_PORT)) {
            if (name.equals(JCReducedConstants.API_METHOD_GETPORT)) {
                if (type.equals("(B)Ljava/mc/ports/Port;")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_GETPORT;
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
            } else if (name.equals(JCReducedConstants.API_METHOD_SETIO)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETIO;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SETPINS)) {
                if (type.equals("(B)V")) {
                    this.id = JCReducedConstants.ID_METHOD_PORTREGISTRY_SETPINS;
                }
            }
        } else if (namePackage.equals(JCReducedConstants.API_PACKAGE_SERIALPORT)) {
            if (name.equals(JCReducedConstants.API_METHOD_RECEIVE)) {
                if (type.equals("()B")) {
                    this.id = JCReducedConstants.ID_METHOD_SERIALPORT_RECEIVE;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_SEND)) {
                if (type.equals("([BSS)V")) {
                    this.id = JCReducedConstants.ID_METHOD_SERIALPORT_SEND;
                }
            }
        } else if (namePackage.equals(JCReducedConstants.API_PACKAGE_TIMER)) {
            if (name.equals(JCReducedConstants.API_METHOD_GETTIMER)) {
                if (type.equals("(B)Ljava/mc/timers/Timer;")) {
                    this.id = JCReducedConstants.ID_METHOD_TIMER_GETTIMER;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_CLEAR)) {
                if (type.equals("()V")) {
                    this.id = JCReducedConstants.ID_METHOD_TIMER_CLEAR;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_ENABLE)) {
                if (type.equals("()V")) {
                    this.id = JCReducedConstants.ID_METHOD_TIMER_ENABLE;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_DISABLE)) {
                if (type.equals("()V")) {
                    this.id = JCReducedConstants.ID_METHOD_TIMER_DISABLE;
                }
            } else if (name.equals(JCReducedConstants.API_METHOD_READ)) {
                if (type.equals("()S")) {
                    this.id = JCReducedConstants.ID_METHOD_TIMER_READ;
                }
            }
        }
    }

}

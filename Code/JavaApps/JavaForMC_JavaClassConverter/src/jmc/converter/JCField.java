package jmc.converter;

public class JCField extends JCFieldOrMethod {

    public JCField(String name, String namePackage, String type, short index,
            byte id, byte idClass) {
        super(name, namePackage, type, index, id, idClass);
        this.setId();
    }

}

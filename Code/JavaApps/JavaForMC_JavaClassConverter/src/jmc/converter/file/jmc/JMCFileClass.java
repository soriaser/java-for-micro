package jmc.converter.file.jmc;

import java.util.Vector;

public class JMCFileClass extends JMCFileTLV {

    private Vector<JMCFileField> fields = new Vector<JMCFileField>();

    private Vector<JMCFileMethod> methods = new Vector<JMCFileMethod>();

    public JMCFileClass() {
        this.tag = JMCFileConstants.TAG_CLASS;
    }

    public JMCFileClass(JMCFileClass jmcClass) {
        this.tag = jmcClass.getTag();
    }

    public void addField(JMCFileField field) {
        fields.add(new JMCFileField(field));
    }

    public void addMethod(JMCFileMethod method) {
        methods.add(new JMCFileMethod(method));
    }

    public JMCFileField getField(int index) {
        return fields.get(index);
    }

    public JMCFileMethod getMethod(int index) {
        return methods.get(index);
    }

    public Vector<JMCFileField> getFields() {
        return new Vector<JMCFileField>(this.fields);
    }

    public Vector<JMCFileMethod> getMethods() {
        return new Vector<JMCFileMethod>(this.methods);
    }

    public int getNumberOfFields() {
        return fields.size();
    }

    public int getNumberOfMethods() {
        return methods.size();
    }
}

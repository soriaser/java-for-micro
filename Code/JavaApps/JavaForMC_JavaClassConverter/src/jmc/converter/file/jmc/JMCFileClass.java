package jmc.converter.file.jmc;

import java.util.Vector;

public class JMCFileClass extends JMCFileTLV {

    private JMCFileFields fields;

    private JMCFileMethods methods;

    public final static int LENGTH_SIZE = 2;

    public JMCFileClass() {
        this.tag = JMCFileConstants.TAG_CLASS;
        this.fields = new JMCFileFields();
        this.methods = new JMCFileMethods();
        this.lengthSize = LENGTH_SIZE;
    }

    public JMCFileClass(JMCFileClass jmcClass) {
        this.tag = jmcClass.getTag();
        this.fields = jmcClass.getJMCFields();
        this.methods = jmcClass.getJMCMethods();
        this.lengthSize = LENGTH_SIZE;
    }

    public void addField(JMCFileField field) {
        this.fields.addField(new JMCFileField(field));
    }

    public void addMethod(JMCFileMethod method) {
        this.methods.addMethod(new JMCFileMethod(method));
    }

    public JMCFileField getField(int index) {
        return this.fields.getField(index);
    }

    public JMCFileMethod getMethod(int index) {
        return this.methods.getMethod(index);
    }

    public Vector<JMCFileField> getFields() {
        return this.fields.getFields();
    }

    public Vector<JMCFileMethod> getMethods() {
        return this.methods.getMethods();
    }

    public JMCFileFields getJMCFields() {
        return new JMCFileFields(this.fields);
    }

    public JMCFileMethods getJMCMethods() {
        return new JMCFileMethods(this.methods);
    }

    public int getNumberOfFields() {
        return this.fields.getNumberOfFields();
    }

    public int getNumberOfMethods() {
        return this.methods.getNumberOfMethods();
    }

    @Override
    public int getLength() {
        int length = 0;

        length += this.fields.getLength();
        length += this.methods.getLength();
        length += this.lengthSize;
        length += 1;

        return length;
    }

    @Override
    public String getValue() {
        String value = "";

        value += this.fields.getTLV();
        value += this.methods.getTLV();

        return value;
    }
}

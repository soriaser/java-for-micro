package jmc.converter.file.jmc;

import java.util.Vector;

import jmc.converter.util.Util;

public class JMCFileClass extends JMCFileTV {

    private JMCFileFields fields;

    private JMCFileMethods methods;

    public JMCFileClass() {
        this.tag = JMCFileConstants.TAG_CLASS;
        this.fields = new JMCFileFields();
        this.methods = new JMCFileMethods();
    }

    public JMCFileClass(JMCFileClass jmcClass) {
        this.tag = jmcClass.getTag();
        this.fields = jmcClass.getJMCFields();
        this.methods = jmcClass.getJMCMethods();
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
    public String getValue() {
        String value = "";

        value += Util.byte2HexString((byte) this.fields.getNumberOfFields());
        value += Util.byte2HexString((byte) this.methods.getNumberOfMethods());

        for (int field = 0; field < this.fields.getNumberOfFields(); field++) {
            value += this.fields.getField(field).getTV();
        }
        
        for (int method = 0; method < this.methods.getNumberOfMethods();
                method++) {
            value += this.methods.getMethod(method).getTLV();
        }

        return value;
    }

}

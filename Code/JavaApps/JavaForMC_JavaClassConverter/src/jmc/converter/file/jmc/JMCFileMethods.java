package jmc.converter.file.jmc;

import java.util.Vector;

public class JMCFileMethods extends JMCFileTLV {
    
    private Vector<JMCFileMethod> methods = new Vector<JMCFileMethod>();

    public final static int LENGTH_SIZE = 2;

    public JMCFileMethods() {
        this.tag = JMCFileConstants.TAG_METHODS;
        this.lengthSize = LENGTH_SIZE;
    }

    public JMCFileMethods(JMCFileMethods methods) {
        this.tag = methods.getTag();
        this.methods = methods.getMethods();
        this.lengthSize = LENGTH_SIZE;
    }

    public void addMethod(JMCFileMethod method) {
        this.methods.add(new JMCFileMethod(method));
    }

    public JMCFileMethod getMethod(int index) {
        return this.methods.get(index);
    }

    public Vector<JMCFileMethod> getMethods() {
        return new Vector<JMCFileMethod>(this.methods);
    }

    public int getNumberOfMethods() {
        return this.methods.size();
    }

    @Override
    public int getLength() {
        int length = 0;

        for (int ii = 0; ii < this.methods.size(); ii++) {
            // Get length from TLV and add length bytes and tag
            length += this.methods.get(ii).getLength() + this.lengthSize + 1;
        }

        return length;
    }

    @Override
    public String getValue() {
        String value = "";

        for (int ii = 0; ii < this.methods.size(); ii++) {
            // Get length from TLV and add length (1 byte) and tag
            value += this.methods.get(ii).getTLV();
        }

        return value;
    }
}

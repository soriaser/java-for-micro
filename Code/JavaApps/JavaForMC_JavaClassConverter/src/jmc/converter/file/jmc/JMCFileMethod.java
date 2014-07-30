package jmc.converter.file.jmc;

import java.util.Arrays;
import java.util.Vector;

public class JMCFileMethod extends JMCFileTLV {

    private byte code[] = null;

    private short id;

    public JMCFileMethod(short id, byte code[]) {
        this.tag = JMCFileConstants.TAG_METHOD;
        this.id = id;
        this.code = Arrays.copyOf(code, code.length);
    }

    public JMCFileMethod(JMCFileMethod method) {
        this.tag = method.getTag();
        this.id = method.getID();
        this.code = method.getCode();
    }

    public byte[] getCode() {
        return Arrays.copyOf(this.code, this.code.length);
    }

    public void setCode(byte code[]) {
        this.code = Arrays.copyOf(code, code.length);
    }

    public short getID() {
        return this.id;
    }

    public void setID(short id) {
        this.id = id;
    }

    public void replaceMethodRefsInCode(Vector<Integer> map) {
        // TODO: replace index of invokespecial and invokevirtual, if required
    }
}

package jmc.converter.file.jmc;

import java.util.Arrays;
import java.util.Vector;

import jmc.converter.util.Util;

import org.apache.bcel.Constants;

public class JMCFileMethod extends JMCFileTLV {

    private byte code[] = null;

    private short id;

    private short locals;

    public final static int LENGTH_SIZE = 2;

    public JMCFileMethod(short id, byte code[], short locals) {
        this.tag = JMCFileConstants.TAG_METHOD;
        this.id = id;
        this.locals = locals;
        this.code = Arrays.copyOf(code, code.length);
        this.lengthSize = LENGTH_SIZE;
    }

    public JMCFileMethod(short id, byte code[]) {
        this.tag = JMCFileConstants.TAG_METHOD;
        this.id = id;
        this.locals = 0;
        this.code = Arrays.copyOf(code, code.length);
        this.lengthSize = LENGTH_SIZE;
    }

    public JMCFileMethod(JMCFileMethod method) {
        this.tag = method.getTag();
        this.id = method.getID();
        this.code = method.getCode();
        this.lengthSize = LENGTH_SIZE;
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

    public short getLocals() {
        return this.locals;
    }

    public void setLocals(short locals) {
        this.locals = locals;
    }


    public void replaceMethodRefsInCode(Vector<Integer> map) {
        for (int ii = 0; ii < code.length; ii++) {
            switch (code[ii]) {
            case (byte) (Constants.INVOKEVIRTUAL & 0x00FF):
            case (byte) (Constants.INVOKESPECIAL & 0x00FF):
                // Next two byte represents the index, increase by one in order
                // to get this value
                ii++;

                // Get index values as short
                short index = (short) (((code[ii] << 8) & 0xFF00)
                        + code[ii + 1]);

                // Replace index if required
                for (int jj = 0; jj < map.size(); jj++) {
                    if ((short) (map.get(jj).intValue() >> 16) == index) {
                        code[ii] = (byte) (map.get(jj).intValue() >> 32);
                        code[ii + 1] = (byte) (map.get(jj).intValue() >> 24);
                        break;
                    }
                }

                // Skip index and go to next bytecode
                ii += 2;
                break;
            }
        }
    }

    @Override
    public int getLength() {
        // Max. Locals + ID + Code
        return (4 + code.length);
    }

    @Override
    public String getValue() {
        String value = "";

        // Max. locals
        value += Util.byte2HexString((byte) (this.locals));
        // ID
        value += Util.byte2HexString((byte) (this.id));
        // Code
        value += Util.byteArray2HexString(this.code);
        
        return value;
    }
}

package jmc.converter;

import jmc.converter.util.Util;

import org.apache.bcel.Constants;

public class JCReducedCode extends JCCode {

    public JCReducedCode(byte[] code) {
        super(code.length);
        this.translate(code);
    }

    private void translate(byte[] code) {
        int offset = 0;

        while (offset < code.length) {
            switch (code[offset]) {
            case Constants.ALOAD_0:
            case Constants.ALOAD_1:
            case Constants.ALOAD_2:
            case Constants.ALOAD_3:
                // Convert to ILOAD_X
                this.appendByte((byte) (code[offset] - 0x10));
                break;
            case Constants.ACONST_NULL:
                this.appendByte((byte) Constants.ICONST_0);
                break;
            case (byte) Constants.INVOKESPECIAL:
            case (byte) Constants.INVOKEVIRTUAL:
            case (byte) Constants.INVOKESTATIC:
                // Same bytecode
                this.appendByte(code[offset]);

                // Go to index and change it by corresponding id
                short index = Util.getShort(code[offset++], code[offset++]);
                this.appendShort(JCMethodMap.getMethodId(index));
                break;
            default:
                this.appendByte(code[offset]);
                break;
            }

            offset++;
        }
    }

}

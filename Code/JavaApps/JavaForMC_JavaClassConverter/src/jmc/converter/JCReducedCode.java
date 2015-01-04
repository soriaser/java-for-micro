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
        short index = 0;

        while (offset < code.length) {
            switch (code[offset]) {
            case Constants.SIPUSH:
                this.appendByte(code[offset++]);
                offset++;
                this.appendShort(Util.getShort(code[offset - 1], code[offset]));
                break;
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
            case (byte) Constants.IFNULL:
                this.appendByte((byte) Constants.IFEQ);
                break;
            case (byte) Constants.IFNONNULL:
                this.appendByte((byte) Constants.IFNE);
                break;
            case (byte) Constants.INVOKESPECIAL:
            case (byte) Constants.INVOKEVIRTUAL:
            case (byte) Constants.INVOKESTATIC:
                // Same bytecode
                this.appendByte(code[offset++]);
                // Get constant pool index
                offset++;
                index = Util.getShort(code[offset - 1], code[offset]);
                // Replace index if required
                this.appendShort(JCMethodMap.getMethodId(index));
                break;
            case (byte) Constants.PUTFIELD:
            case (byte) Constants.GETFIELD:
                // Same bytecode
                this.appendByte(code[offset++]);
                // Get constant pool index
                offset++;
                index = Util.getShort(code[offset - 1], code[offset]);
                // Replace index if required
                this.appendShort(JCFieldMap.getFieldId(index));
                break;
            default:
                this.appendByte(code[offset]);
                break;
            }

            offset++;
        }
    }

}

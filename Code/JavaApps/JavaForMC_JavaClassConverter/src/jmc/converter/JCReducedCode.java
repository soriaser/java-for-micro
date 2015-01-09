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
        int increment = 0;
        int tmp = 0;

        while (offset < code.length) {
            increment = 1;

            switch (code[offset]) {
            case Constants.SIPUSH:
                this.appendByte(code[offset]);
                this.appendShort(getNextBytes(code, offset, 2));
                increment = 3;
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
                this.appendShort(getNextBytes(code, offset, 2));
                increment = 3;
                break;
            case (byte) Constants.IFNONNULL:
                this.appendByte((byte) Constants.IFNE);
                this.appendShort(getNextBytes(code, offset, 2));
                increment = 3;
                break;
            case (byte) Constants.IINC:
            case (byte) Constants.IFEQ:
            case (byte) Constants.IFNE:
            case (byte) Constants.IFLT:
            case (byte) Constants.IFGE:
            case (byte) Constants.IFGT:
            case (byte) Constants.IFLE:
            case (byte) Constants.IF_ICMPEQ:
            case (byte) Constants.IF_ICMPNE:
            case (byte) Constants.IF_ICMPLT:
            case (byte) Constants.IF_ICMPGE:
            case (byte) Constants.IF_ICMPGT:
            case (byte) Constants.IF_ICMPLE:
            case (byte) Constants.GOTO:
                this.appendByte(code[offset]);
                this.appendShort(getNextBytes(code, offset, 2));
                increment = 3;
                break;
            case (byte) Constants.I2B:
            case (byte) Constants.I2C:
            case (byte) Constants.I2S:
                this.appendByte((byte) Constants.NOP);
                break;
            case (byte) Constants.INVOKESPECIAL:
            case (byte) Constants.INVOKEVIRTUAL:
            case (byte) Constants.INVOKESTATIC:
                // Same bytecode
                this.appendByte(code[offset]);
                // Get constant pool index
                tmp = getNextBytes(code, offset, 2);
                // Replace index if required
                this.appendShort(JCMethodMap.getMethodId((short) tmp));

                increment = 3;
                break;
            case (byte) Constants.PUTSTATIC:
            case (byte) Constants.GETSTATIC:
            case (byte) Constants.PUTFIELD:
            case (byte) Constants.GETFIELD:
                // Same bytecode
                this.appendByte(code[offset]);
                // Get constant pool index
                tmp = getNextBytes(code, offset, 2);
                // Replace index if required
                this.appendShort(JCFieldMap.getFieldId((short) tmp));

                increment = 3;
                break;
            default:
                this.appendByte(code[offset]);
                break;
            }

            offset += increment;
        }
    }

    private short getNextBytes(byte[] code, int offset, int bytes) {
        offset++;
        return Util.getShort(code[offset], code[offset + 1]);
    }

}

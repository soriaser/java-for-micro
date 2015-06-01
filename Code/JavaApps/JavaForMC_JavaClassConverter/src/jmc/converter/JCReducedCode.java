package jmc.converter;

import jmc.converter.util.Util;

import org.apache.bcel.Constants;

public class JCReducedCode extends JCCode {

    public JCReducedCode(byte[] code) {
        super(code.length);
        this.translate(code);
    }

    private void translate(byte[] code) {
        int delta = 0;
        int offset = 0;
        int increment = 0;
        int tmp = 0;

        while (offset < code.length) {
            increment = 1;

            switch (code[offset]) {
            case Constants.SIPUSH:
                this.appendByte(code[offset]);
                this.appendShort((short) getNextBytes(code, offset, 2));
                increment = 3;
                break;
            case Constants.ASTORE:
                this.appendByte((byte) Constants.ISTORE);
                break;
            case Constants.ASTORE_0:
            case Constants.ASTORE_1:
            case Constants.ASTORE_2:
            case Constants.ASTORE_3:
                this.appendByte((byte) (code[offset] - 0x10));
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
                this.appendShort((short) getNextBytes(code, offset, 2));
                increment = 3;
                break;
            case (byte) Constants.IFNONNULL:
                this.appendByte((byte) Constants.IFNE);
                this.appendShort((short) getNextBytes(code, offset, 2));
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
                this.appendShort((short) getNextBytes(code, offset, 2));
                increment = 3;
                break;
            case (byte) Constants.I2B:
            case (byte) Constants.I2C:
            case (byte) Constants.I2S:
                this.appendByte((byte) Constants.NOP);
                break;
            /*
            case (byte) Constants.TABLESWITCH:
                offset++;
                while (offset % 4 != 0) {
                    this.appendByte((byte) Constants.NOP);
                    delta++;
                    offset++;
                }
                offset--;

                this.appendByte((byte) Constants.TABLESWITCH);
                
                this.appendInt(getNextBytes(code, offset, 4) - delta);
                offset += 4;

                int low  = getNextBytes(code, offset, 4);
                int high = getNextBytes(code, offset + 4, 4);
                offset += 8;

                for (int ii = 0; ii < (high - low + 1); ii++) {
                    this.appendInt(getNextBytes(code, offset, 4) - delta);
                    offset += 4;
                }
                break;
            case (byte) Constants.LOOKUPSWITCH:
                offset++;
                while (offset % 4 != 0) {
                    this.appendByte((byte) Constants.NOP);
                    delta++;
                    offset++;
                }
                offset--;

                this.appendByte((byte) Constants.LOOKUPSWITCH);

                this.appendInt(getNextBytes(code, offset, 4) - delta);
                offset += 4;

                int count = getNextBytes(code, offset, 4);
                offset += 4;

                for (int ii = 0; ii < count; ii++) {
                    offset += 4;
                    this.appendInt(getNextBytes(code, offset, 4) - delta);
                    offset += 4;
                }
                break;
            */
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
            case (byte) Constants.NEWARRAY:
                this.appendByte(code[offset]);

                if (code[offset + 1] != 0x08) {
                    System.out.println("Only byte array supported");
                    System.exit(0);
                }

                increment++;
            default:
                this.appendByte(code[offset]);
                break;
            }

            offset += increment;
        }
    }

    private int getNextBytes(byte[] code, int offset, int bytes) {
        offset++;

        switch (bytes) {
        case 2:
            return Util.getShort(code[offset], code[offset + 1]);
        case 4:
            return Util.getInteger(code[offset], code[offset + 1],
                code[offset + 2], code[offset + 3]);
        }

        return 0;
    }

}

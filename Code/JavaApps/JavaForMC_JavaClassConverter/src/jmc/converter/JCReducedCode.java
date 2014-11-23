package jmc.converter;

import org.apache.bcel.Constants;

public class JCReducedCode {

    private byte[] code;

    public JCReducedCode(byte code[]) {
        this.code = this.translate(code);
    }

    public byte[] getCode() {
        return this.code;
    }

    private byte[] translate(byte[] code) {
        int offsetCode = 0;
        int offsetCodeTranslated = 0;

        byte[] codeTranslated = new byte[code.length];

        while (offsetCode < code.length) {
            switch (code[offsetCode]) {
            case Constants.ALOAD_0:
            case Constants.ALOAD_1:
            case Constants.ALOAD_2:
            case Constants.ALOAD_3:
                // Convert to ILOAD_X
                codeTranslated[offsetCodeTranslated] =
                    (byte) (code[offsetCode] - 0x10);
                break;
            case Constants.ACONST_NULL:
                codeTranslated[offsetCodeTranslated] = Constants.ICONST_0;
                break;
            default:
                codeTranslated[offsetCodeTranslated] = code[offsetCode];
                break;
            }

            offsetCode++;
            offsetCodeTranslated++;
        }

        return codeTranslated;
    }

}

package jmc.converter;

import org.apache.bcel.classfile.Method;

public class JCReducedMethod {

    public final static byte SIZE_HEADER = 8;

    private final static byte FLAG_INIT_METHOD = 0x01;

    private JCReducedCode code;

    private byte arguments;

    private byte locals;

    private byte stack;

    private byte id;
    
    private byte idc;

    private boolean isInit;

    private boolean isMain;

    public JCReducedMethod(Method method, byte id, byte idc) {
        this.code = new JCReducedCode(method.getCode().getCode());

        if (method.getCode().getMaxLocals() > 255) {
            throw new InternalError("Maximum locals exceed maximum allowed");
        }
        
        this.locals = (byte) method.getCode().getMaxLocals();

        if (method.getCode().getMaxStack() > 255) {
            throw new InternalError("Maximum stack exceed maximum allowed");
        }
        
        this.stack = (byte) method.getCode().getMaxStack();

        this.isInit = false;
        if (method.getName().equals("<init>")) {
            this.isInit = true;
        }

        this.isMain = false;
        if (method.getName().equals("main")) {
            this.isMain = true;
        }

        this.arguments = JCParser.getNumberOfArguments(method);

        this.id  = id;
        this.idc = idc;
    }

    public byte[] getByteCode() {
        return this.code.getCode();
    }

    public byte getClassId() {
        return this.idc;
    }

    public byte getFlags() {
        byte flags = 0x00;

        if (this.isInit) {
            flags |= FLAG_INIT_METHOD;
        }

        return flags;
    }

    public byte getId() {
        return this.id;
    }

    public byte getMaximumLocals() {
        return this.locals;
    }

    public byte getMaximumStack() {
        return this.stack;
    }

    public byte getNumberOfArguments() {
        return this.arguments;
    }

    public boolean isInit() {
        return this.isInit;
    }

    public boolean isMain() {
        return this.isMain;
    }

}

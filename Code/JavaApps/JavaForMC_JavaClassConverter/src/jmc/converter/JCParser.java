package jmc.converter;

import java.io.IOException;

import org.apache.bcel.Constants;
import org.apache.bcel.classfile.ClassFormatException;
import org.apache.bcel.classfile.ClassParser;
import org.apache.bcel.classfile.ConstantPool;
import org.apache.bcel.classfile.Field;
import org.apache.bcel.classfile.JavaClass;
import org.apache.bcel.classfile.Method;
import org.apache.bcel.generic.Type;

public class JCParser {

    private JavaClass jClass;

    public JCParser(String pathAndFileName) {
        try {
            this.jClass = (new ClassParser(pathAndFileName)).parse();
        } catch (ClassFormatException | IOException e) {
            e.printStackTrace();
        }
    }

    public byte getNumberOfArguments(Method method) {
        int arguments = 0;
        Type[] types = method.getArgumentTypes();

        for (int ii = 0; ii < types.length; ii++) {
            switch (types[ii].getType()) {
            case Constants.T_BYTE:
            case Constants.T_CHAR:
            case Constants.T_SHORT:
            case Constants.T_BOOLEAN:
                arguments++;
                break;
            case Constants.T_ARRAY:
                break;
            default:
                throw new InternalError("Argument not allowed");
            }
        }

        if (arguments > 255) {
            throw new InternalError("Number of arguments exceed maximum" +
                    "allowed");
        }

        return (byte) arguments;
    }

    public byte getNumberOfMethods() {
        int methods = this.jClass.getMethods().length;

        if (methods > 255) {
            throw new InternalError("Number of methods exceed maximum allowed");
        }

        return (byte) methods;
    }

    public byte getNumberOfClasses() {
        return 0x01;
    }

    public short getNumberOfConstants(byte type) {
        short constants = 0;

        ConstantPool pool = this.jClass.getConstantPool();
        for (int ii = 0; ii < (int) pool.getLength(); ii++) {
            if (pool.getConstant(ii) != null) {
                if (pool.getConstant(ii).getTag() == type) {
                    constants++;
                }
            }
        }

        return constants;
    }

    public byte getNumberOfStaticFields() {
        int fields = 0;

        for (int ii = 0; ii < (int) this.jClass.getFields().length; ii++) {
            Field field = this.jClass.getFields()[ii];
            if (field.isStatic()) {
                fields++;
            }
        }

        if (fields > 255) {
            throw new InternalError("Number of static fields" +
                    "exceed maximum allowed");
        }

        return (byte) fields;
    }

    public byte getClassId() {
        return 0x00;
    }

    public byte getMainMethodIndex() {
        if (this.jClass.getMethods().length > 255) {
            throw new InternalError("Number of methods exceed maximum allowed");
        }

        for (byte ii = 0; ii < (byte) this.jClass.getMethods().length; ii++) {
            if (this.jClass.getMethods()[ii].getName().equals("main")) {
                return ii;
            }
        }

        throw new InternalError("Main method doesn't found");
    }

    public short getSizeOfAllStrings() {
        String string = "";

        ConstantPool pool = this.jClass.getConstantPool();
        for (int ii = 0; ii < (int) pool.getLength(); ii++) {
            if (pool.getConstant(ii) != null) {
                if (pool.getConstant(ii).getTag() ==
                        Constants.CONSTANT_String) {
                    string += pool.getConstantString(ii,
                            Constants.CONSTANT_String);
                }
            }
        }

        if ((short) string.length() > 65535) {
            throw new InternalError("Total strings size exceeds" +
                    "maximum allowed");
        }

        return (short) string.length();
    }

    public Method getMethod(int index) {
        return this.jClass.getMethods()[index];
    }
}

package jmc.converter;

import java.io.IOException;

import org.apache.bcel.Constants;
import org.apache.bcel.classfile.ClassFormatException;
import org.apache.bcel.classfile.ClassParser;
import org.apache.bcel.classfile.ConstantPool;
import org.apache.bcel.classfile.Field;
import org.apache.bcel.classfile.JavaClass;

public class JCParser {

    private JavaClass jClass;

    public JCParser(String pathAndFileName) {
        try {
            this.jClass = (new ClassParser(pathAndFileName)).parse();
        } catch (ClassFormatException | IOException e) {
            e.printStackTrace();
        }
    }

    public byte getNumberOfMethods() {
        return (byte) this.jClass.getMethods().length;
    }

    public byte getNumberOfClasses() {
        return 0x01;
    }

    public short getNumberOfConstants(byte type) {
        short constants = 0;

        ConstantPool pool = this.jClass.getConstantPool();
        for (int ii = 0; ii < (int) pool.getLength(); ii++) {
            if (pool.getConstant(ii).getTag() == type) {
                constants++;
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
            string += pool.getConstantString(ii, Constants.CONSTANT_String);
        }

        if ((short) string.length() > 65535) {
            throw new InternalError("Total strings size exceeds" +
                    "maximum allowed");
        }

        return (short) string.length();
    }
}

package jmc.converter;

import java.io.IOException;

import org.apache.bcel.classfile.ClassFormatException;
import org.apache.bcel.classfile.ClassParser;
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

    public short getMainMethodIndex() {
        for (short ii = 0; ii < (short) this.jClass.getMethods().length; ii++) {
            if (this.jClass.getMethods()[ii].getName().equals("main")) {
                return ii;
            }
        }

        throw new InternalError("Main method doesn't found");
    }
}

package jmc.converter;

import java.io.IOException;

import jmc.converter.util.Util;

import org.apache.bcel.classfile.ClassFormatException;
import org.apache.bcel.classfile.ClassParser;
import org.apache.bcel.classfile.JavaClass;

public class JCReducedFile extends JCFile {

    private final static String EXTENSION = "jcr";

    private final static short JCR_HEADER_SIZE = 16;

    private JCReduced jcReduced = null;

    private short offsetToCode = 0;

    public JCReducedFile(String classFiles[], int main) {
        super(classFiles[main], EXTENSION);

        JavaClass javaclasses[] = new JavaClass[classFiles.length];

        try {
            for (int ii = 0; ii < classFiles.length; ii++) {
                javaclasses[ii] = (new ClassParser(classFiles[ii])).parse();
            }    
        } catch (ClassFormatException | IOException exception) {
            exception.printStackTrace();
        }

        JCFieldMap.fill(javaclasses);
        JCMethodMap.fill(javaclasses);
        this.jcReduced = new JCReduced(javaclasses);
    }

    public void fill() {
        this.writeHeader();
        this.writeClasses();
        this.writeConstants();
        this.writeMethods();
    }

    /**
     * Writes following C structure representing Java class
     *     struct javaclass_class_t {
     *         uint8_t  super;
     *         uint8_t  fields;
     *         };
     *
     * @param jcrClass JCReducedClass object.
     */
    private void writeClass(JCReducedClass jcrClass) {
        this.writeByte(jcrClass.getSuperClass());
        this.writeByte(jcrClass.getFields());
    }

    private void writeClasses() {
        for (int ii = 0; ii < this.jcReduced.getNumberOfClasses(); ii++) {
            this.writeClass(this.jcReduced.getClass(ii));
        }
    }

    private void writeConstants() {
        for (int ii = 0; ii < this.jcReduced.getNumberOfConstants(); ii++) {
            this.writeShort(this.jcReduced.getConstant(ii));
        }
    }

    /**
     * Writes following C structure representing Java Class header:
     *     struct javaclass_header {
     *         uint8_t  version;
     *         uint8_t  methods;
     *         uint16_t constants;
     *         uint8_t  classes;
     *         uint8_t  fields;
     *         uint8_t  main;
     *         uint8_t  onLoad;
     *         uint16_t offsetClasses;
     *         uint16_t offsetConstants;
     *         uint16_t offsetStrings;
     *         uint16_t offsetMethods;
     *     };
     */
    private void writeHeader() {
        short offset = 0;

        this.writeByte (this.jcReduced.getVersion());
        this.writeByte (this.jcReduced.getNumberOfMethods());
        this.writeShort(this.jcReduced.getNumberOfConstants());
        this.writeByte (this.jcReduced.getNumberOfClasses());
        this.writeByte (this.jcReduced.getNumberOfStaticFields());
        this.writeByte (this.jcReduced.getMainMethodIndex());
        this.writeByte (this.jcReduced.getOnLoadMethodIndex());

        offset = JCR_HEADER_SIZE;
        // Offset to Classes
        this.writeShort(offset);

        offset += this.jcReduced.getNumberOfClasses() * JCReducedClass.SIZE;
        // Offset to Constants
        this.writeShort(offset);

        offset += this.jcReduced.getNumberOfConstants() *
                JCReduced.SIZE_CONSTANT;
        // Offset to Strings
        this.writeShort(offset);

        offset += this.jcReduced.getNumberOfStrings() *
                JCReduced.SIZE_STRING_INDEX;
        offset += this.jcReduced.getAllStringsSize();
        // Offset to Methods
        this.writeShort(offset);

        offset += this.jcReduced.getNumberOfMethods() *
                JCReducedMethod.SIZE_HEADER;
        // Offset to Code
        this.offsetToCode = offset;
    }

    private void writeMethodCode(JCReducedMethod method) {
        this.writeArray(method.getByteCode());
    }

    /**
     * Writes following C structure representing Java method header
     *     struct javaclass_method_header_t {
     *         uint16_t code;
     *         uint16_t id;
     *         uint8_t  flags;
     *         uint8_t  arguments;
     *         uint8_t  locals;
     *         uint8_t  stack;
     *         };
     *
     * @param method JCReduced Method.
     */
    private void writeMethodHeader(JCReducedMethod method) {
        this.writeShort(this.offsetToCode);
        this.offsetToCode += method.getByteCode().length;

        this.writeShort(Util.getShort(method.getClassId(), method.getId()));
        this.writeByte(method.getFlags());
        this.writeByte(method.getNumberOfArguments());
        this.writeByte(method.getMaximumLocals());
        this.writeByte(method.getMaximumStack());
    }

    private void writeMethods() {
        for (byte ii = 0; ii < this.jcReduced.getNumberOfMethods(); ii++) {
            this.writeMethodHeader(this.jcReduced.getMethod(ii));
        }

        for (byte ii = 0; ii < this.jcReduced.getNumberOfMethods(); ii++) {
            this.writeMethodCode(this.jcReduced.getMethod(ii));
        }
    }

}

package jmc.converter;

import org.apache.bcel.Constants;
import org.apache.bcel.classfile.Code;
import org.apache.bcel.classfile.Method;

public class JCReducedFile extends JCFile {

    private final static String EXTENSION = "jcr";

    private final static byte VERSION = 0x01;

    private final static byte FLAG_INIT_METHOD = 0x01;

    private final static short JCR_HEADER_CLASS_SIZE = 2;

    private final static short JCR_HEADER_METHODS_SIZE = 8;

    private final static short JCR_CONSTANT_SIZE = 4;

    private final static short JCR_STRING_SIZE = 2;

    private JCParser jcParser = null;

    private short offsetToClasses = 0;

    private short offsetToConstants = 0;

    private short offsetToStrings = 0;

    private short offsetToMethods = 0;

    private short offsetToCode = 0;

    public JCReducedFile(String pathAndFileName) {
        super(pathAndFileName, EXTENSION);
        this.jcParser = new JCParser(pathAndFileName);
    }

    public void fill() {
        this.writeHeader();

        // Temporal loop to write empty bytes until methods
        while (this.getSize() < this.offsetToMethods) {
            this.writeByte((byte) 0xFF);
        }

        this.writeMethods();
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
     *         uint16_t offsetClasses;
     *         uint16_t offsetConstants;
     *         uint16_t offsetStrings;
     *         uint16_t offsetMethods;
     *     };
     */
    private void writeHeader() {
        short offset = 0;

        // Version byte
        this.writeByte(VERSION);
        offset++;
        // Number of methods
        this.writeByte(this.jcParser.getNumberOfMethods());
        offset++;
        // Number of constants
        this.writeShort(this.jcParser.getNumberOfConstants(
                Constants.CONSTANT_Integer));
        offset++;
        offset++;
        // Number of classes
        this.writeByte(this.jcParser.getNumberOfClasses());
        offset++;
        // Number of Static Fields
        this.writeByte(this.jcParser.getNumberOfStaticFields());
        offset++;
        // Main method index
        this.writeByte(this.jcParser.getMainMethodIndex());
        offset++;

        // Write offsets
        //     + Offset Classes (+2)
        //     + Offset Constants (+2)
        //     + Offset Strings (+2)
        //     + Offset Methods (+2)
        offset += 8;
        // Classes offset = (Header Size)
        this.offsetToClasses = offset;
        this.writeShort(offset);
        // Constants offset = (Header Size) + (Number of Classes * 2 Bytes)
        // 2 bytes corresponds to super id and number of fields, every class
        // header has these 2 bytes
        offset += JCR_HEADER_CLASS_SIZE * this.jcParser.getNumberOfClasses();
        this.offsetToConstants = offset;
        this.writeShort(offset);
        // Strings offset = (Header Size) + (Number of Classes * 2 Bytes) +
        // (Number of constants * 4 Bytes)
        offset += JCR_CONSTANT_SIZE * this.jcParser.getNumberOfConstants(
                Constants.CONSTANT_Integer);
        this.offsetToStrings = offset;
        this.writeShort(offset);
        // Methods offset = (Header Size) + (Number of Classes * 2 Bytes) +
        // (Number of constants * 4 Bytes) + (Number of strings * 2 Bytes) +
        // Strings (X Bytes)
        offset += JCR_STRING_SIZE * this.jcParser.getNumberOfConstants(
                Constants.CONSTANT_String);
        offset += this.jcParser.getSizeOfAllStrings();
        this.offsetToMethods = offset;
        this.writeShort(offset);
        // Code offset = (Header Size) + (Number of Classes * 2 Bytes) +
        // (Number of constants * 4 Bytes) + (Number of strings * 2 Bytes) +
        // Strings (X Bytes) + (Number of methods * Method header size)
        offset += JCR_HEADER_METHODS_SIZE * this.jcParser.getNumberOfMethods();
        // It is not written, just stored
        this.offsetToCode = offset;
    }

    /**
     * Writes all method headers as described in writeMethod description. It
     * starts at methods offset set in Java Class header.
     */
    private void writeMethods() {
        // Write all method headers
        for (byte id = 0; id < this.jcParser.getNumberOfMethods(); id++) {
            this.writeMethodHeader(id, this.jcParser.getMethod(id));
        }

        // Write all methods code
        for (byte id = 0; id < this.jcParser.getNumberOfMethods(); id++) {
            this.writeMethodCode(this.jcParser.getMethod(id).getCode());
        }
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
     * @param id Method ID.
     * @param method Object org.apache.bcel.classfile.Method.
     */
    private void writeMethodHeader(byte id, Method method) {
        // Write offset to bytecode of this method.
        this.writeShort(this.offsetToCode);
        // Write method id (class id + method id)
        this.writeByte(this.jcParser.getClassId());
        this.writeByte(id);

        // Write flags:
        // If <init> method, bit 0 is set to 1        
        byte flags = 0x00;
        if (method.getName().equals("<init>")) {
            flags |= FLAG_INIT_METHOD;
        }
        this.writeByte(flags);

        // Write number of arguments
        this.writeByte(this.jcParser.getNumberOfArguments(method));

        int locals = method.getCode().getMaxLocals();
        int stack = method.getCode().getMaxStack();

        if ((locals > 255) || (stack > 255)) {
            throw new InternalError("Maximum locals and stack are 255");
        }
        
        // Write maximum number of locals and stack
        this.writeByte((byte) locals);
        this.writeByte((byte) stack);
        
        // Increase code offset to put 
        this.offsetToCode += method.getCode().getLength();
    }

    /**
     * Writes Java method bytecode.
     *
     * @param code Object org.apache.bcel.classfile.Code.
     */
    private void writeMethodCode(Code code) {
        byte bytecodes[] = code.getCode();

        for (int ii = 0; ii < bytecodes.length; ii++) {
            switch (bytecodes[ii]) {
            case Constants.ALOAD_0:
                bytecodes[ii] = Constants.ILOAD_0;
                break;
            case Constants.ALOAD_1:
                bytecodes[ii] = Constants.ILOAD_1;
                break;
            case Constants.ALOAD_2:
                bytecodes[ii] = Constants.ILOAD_2;
                break;
            case Constants.ALOAD_3:
                bytecodes[ii] = Constants.ILOAD_3;
                break;
            }
        }

        this.writeArray(code.getCode());
    }
}

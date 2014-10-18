package jmc.converter;

import org.apache.bcel.Constants;

public class JCReducedFile extends JCFile {

    private final static String EXTENSION = "jcr";

    private final static byte VERSION = 0x01;

    private final static short JCR_HEADER_CLASS_SIZE = 2;

    private final static short JCR_CONSTANT_SIZE = 4;

    private final static short JCR_STRING_SIZE = 2;

    private JCParser jcParser = null;

    public JCReducedFile(String pathAndFileName) {
        super(pathAndFileName, EXTENSION);
        this.jcParser = new JCParser(pathAndFileName);
    }

    public void fill() {
        this.writeHeader();
    }

    /**
     * Tries to write following C structure:
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
        this.writeShort(this.jcParser.getMainMethodIndex());
        offset++;
        offset++;

        // Write offsets
        //     + Offset Classes (+2)
        //     + Offset Constants (+2)
        //     + Offset Strings (+2)
        //     + Offset Methods (+2)
        offset += 8;
        // Classes offset = (Header Size)
        this.writeShort(offset);
        // Constants offset = (Header Size) + (Number of Classes * 2 Bytes)
        // 2 bytes corresponds to super id and number of fields, every class
        // header has these 2 bytes
        offset += JCR_HEADER_CLASS_SIZE * this.jcParser.getNumberOfClasses();
        this.writeShort(offset);
        // Strings offset = (Header Size) + (Number of Classes * 2 Bytes) +
        // (Number of constants * 4 Bytes)
        offset += JCR_CONSTANT_SIZE * this.jcParser.getNumberOfConstants(
                Constants.CONSTANT_Integer);
        this.writeShort(offset);
        // Methods offset = (Header Size) + (Number of Classes * 2 Bytes) +
        // (Number of constants * 4 Bytes) + (Number of strings * 2 Bytes) +
        // Strings (X Bytes)
        offset += JCR_STRING_SIZE * this.jcParser.getNumberOfConstants(
                Constants.CONSTANT_String);
        offset += this.jcParser.getSizeOfAllStrings();
        this.writeShort(offset);
    }
}

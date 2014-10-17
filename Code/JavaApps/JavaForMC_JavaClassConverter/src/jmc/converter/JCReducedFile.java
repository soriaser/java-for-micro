package jmc.converter;

import java.io.IOException;

public class JCReducedFile extends JCFile {

    private final static String EXTENSION = "jcr";

    private final static byte VERSION = 0x01;

    private final static short JCR_HEADER_SIZE = 11;

    private final static short JCR_HEADER_CLASS_SIZE = 2;

    private JCParser jcParser = null;

    public JCReducedFile(String pathAndFileName) {
        super(pathAndFileName, EXTENSION);
        this.jcParser = new JCParser(pathAndFileName);
    }

    public void create() {
        short offset = JCR_HEADER_SIZE;

        // Version byte
        this.writeByte(VERSION);
        // Number of methods
        this.writeByte(this.jcParser.getNumberOfMethods());
        // Main method index
        this.writeShort(this.jcParser.getMainMethodIndex());
        // Constants offset = (Header Size) + (Number of Classes * 2 Bytes)
        // 2 bytes corresponds to super id and number of fields, every class
        // header has these 2 bytes
        offset += JCR_HEADER_CLASS_SIZE;
        this.writeShort(offset);

        try {
            this.oFileBuffer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

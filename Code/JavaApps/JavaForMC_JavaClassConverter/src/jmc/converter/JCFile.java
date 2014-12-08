package jmc.converter;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import jmc.converter.util.Util;

public class JCFile {

    private File oFile = null;

    private int size = 0;

    protected BufferedWriter oFileBuffer = null;

    public JCFile(String pathAndFileName) {
        this.oFile = new File(pathAndFileName);
    }

    public JCFile(String pathAndFileName, String fileExtension) {
        // Remove last file extension and add new one
        if (pathAndFileName.contains(".")) {
            // Remove last file extension
            pathAndFileName = pathAndFileName.substring(0,
                    pathAndFileName.lastIndexOf("."));
            // Add new file extension
            pathAndFileName += ".";
            pathAndFileName += fileExtension;
        }

        // Create new output file
        this.oFile = new File(pathAndFileName);
    }

    public void fill() {};

    public void create() {
        this.start();
        this.fill();
        this.finalize();
    }

    public void finalize() {
        try {
            this.oFileBuffer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void start() {
        try {
            // Create output file buffer
            this.oFileBuffer = new BufferedWriter(new FileWriter(this.oFile));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeArray(byte array[]) {
        for (int ii = 0; ii < array.length; ii++) {
            this.writeByte(array[ii]);
        }
    }

    public void writeByte(byte value) {
        try {
            this.oFileBuffer.write(Util.byte2HexString(value));
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.size++;
    }

    public void writeShort(short value) {
        if (JCConverter.isLittleEndian) {
            value = Util.revert(value);
        }

        this.writeByte((byte) (value >> 8));
        this.writeByte((byte) (value >> 0));
    }

    public void writeInt(int value) {
        if (JCConverter.isLittleEndian) {
            value = Util.revert(value);
        }

        this.writeByte((byte) (value >> 24));
        this.writeByte((byte) (value >> 16));
        this.writeByte((byte) (value >>  8));
        this.writeByte((byte) (value >>  0));        
    }

    public int getSize() {
        return this.size;
    }

}

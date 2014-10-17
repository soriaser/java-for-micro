package jmc.converter;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import jmc.converter.util.Util;

public class JCFile {

    private File oFile = null;

    protected BufferedWriter oFileBuffer = null;

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

        try {
            // Create output file buffer
            this.oFileBuffer = new BufferedWriter(new FileWriter(this.oFile));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeByte(byte value) {
        try {
            this.oFileBuffer.write(Util.byte2HexString(value));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeShort(short value) {
        this.writeByte((byte) (value >> 8));
        this.writeByte((byte) (value));
    }
}

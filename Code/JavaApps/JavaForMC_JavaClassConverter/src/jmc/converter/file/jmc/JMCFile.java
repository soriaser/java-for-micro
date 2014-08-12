package jmc.converter.file.jmc;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Vector;

import jmc.converter.util.Util;

public class JMCFile {

    private Vector<JMCFileClass> classes = new Vector<JMCFileClass>();

    public JMCFile() {}

    public void addClass(JMCFileClass jmcClass) {
        this.classes.add(new JMCFileClass(jmcClass));
    }

    public JMCFileClass getClass(int index) {
        return this.classes.get(index);
    }

    public int getNumberOfClasses() {
        return this.classes.size();
    }

    public void createOutputFile(String fileName) {
        File file = null;
        BufferedWriter fileOutput = null;

        try {
            file = new File(fileName);
            fileOutput = new BufferedWriter(new FileWriter(file));

            // Write Version
            fileOutput.write(Util.byte2HexString(JMCFileConstants.VERSION_MSB));
            fileOutput.write(Util.byte2HexString(JMCFileConstants.VERSION_LSB));

            for (int ii = 0; ii < classes.size(); ii++) {
                fileOutput.write(classes.get(ii).getTLV());
            }

            fileOutput.close();
        } catch (IOException e) {
            System.out.println("Error creating JMC file ouput");
            System.exit(0);
        }
    }
}

package jmc.converter;

public class JCConverter {

    /**
     * Starts class to JMC converter.
     *
     * @param args At least one argument containing *.class file path
     */
    public static void main(String[] args) {
        String classPathAndFileName = "";
        boolean isLittleEndian = false;

        // Read options
        for (int option = 0; option < args.length; option++) {
            // Class file
            if (args[option].equals("--class") ||
                args[option].equals("-c")) {
                option++;
                classPathAndFileName = args[option];
            }
            // Little Endian
            if (args[option].equals("--littleEndian") ||
                args[option].equals("-le")) {
                isLittleEndian = true;
            }
            // Big Endian
            if (args[option].equals("--bigEndian") ||
                args[option].equals("-be")) {
                isLittleEndian = false;
            }
        }

        if (classPathAndFileName.length() == 0) {
            System.out.println("File not present in arguments");
            System.exit(0);
        }

        JCReducedFile JCRFile = new JCReducedFile(classPathAndFileName);

        if (isLittleEndian) {
            JCRFile.setLittleEndian();
        }

        JCRFile.create();
    }
}

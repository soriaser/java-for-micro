package jmc.converter;

public class JCConverter {

    /**
     * Starts class to JMC converter.
     *
     * @param args At least one argument containing *.class file path
     */
    public static void main(String[] args) {
        // TODO: Add support for more than one *.class file
        String files[] = new String[1];
        boolean isLittleEndian = false;

        // Read options
        for (int option = 0; option < args.length; option++) {
            // Class file
            if (args[option].equals("--classes") ||
                args[option].equals("-c")) {
                option++;
                files[0] = args[option];
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

        if (files[0].length() == 0) {
            System.out.println("File not present in arguments");
            System.exit(0);
        }

        JCReducedFile JCRFile = new JCReducedFile(files, 0);

        if (isLittleEndian) {
            JCRFile.setLittleEndian();
        }

        JCRFile.create();
    }
}

package jmc.serial;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.math.BigInteger;

import jssc.SerialPortList;

public class SerialSender {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // Print ports option requested
        boolean optPrintPorts = false;
        // Load file
        boolean optLoadFile = false;

        // Port chosen to read and write
        String optPort = "";

        // File containing data to send
        String optFile = "";

        // Read options
        for (int option = 0; option < args.length; option++) {
            // Print ports option
            if (args[option].equals("--ports") ||
                args[option].equals("-ps")) {
                optPrintPorts = true;
            }

            // Choose port option
            if (args[option].equals("--port") ||
                    args[option].equals("-p")) {
                optPort = args[option + 1];
            }

            // File with data to send
            if (args[option].equals("--file") ||
                    args[option].equals("-f")) {
                optFile = args[option + 1];
                optLoadFile = true;
            }
        }

        // Print Ports
        if (optPrintPorts) {
            String[] portNames = SerialPortList.getPortNames();

            System.out.println("Available Ports:\n");
            for(int i = 0; i < portNames.length; i++){
                System.out.println(portNames[i]);
            }
        }

        // Read file data and send data by port
        if ((optFile.length() > 0) && (optPort.length() > 0)) {
            String hexStringData = "";

            try {
                FileInputStream fStream = new FileInputStream(optFile);
                DataInputStream input = new DataInputStream(fStream);
                BufferedReader buffer = new BufferedReader(
                        new InputStreamReader(input));

                String line;
                // Read File Line By Line
                while ((line = buffer.readLine()) != null) {
                    hexStringData += line;
                }

                input.close();
            } catch (Exception exception) {
                System.out.println(exception);
            }

            byte instruction = 0x00;
            byte[] command = null;
            byte[] data = null;

            if (optLoadFile) {
                data = new BigInteger(hexStringData, 16).toByteArray();
                //data = hexStringData.getBytes();
                instruction = 0x10;
            }

            // CLA + INS
            short commandSize = 2;
            short offset = 0;

            if (data != null) {
                // CLA + INS + Length (2 bytes) + data
                commandSize += 2 + data.length;
            }

            // Header
            command = new byte[commandSize];
            command[offset++] = 0x00;
            command[offset++] = instruction;

            // Length + data
            if (data != null) {
                // Length
                command[offset++] = (byte) (data.length >> 8);
                command[offset++] = (byte) (data.length);
                // Data
                System.arraycopy(data, (short) 0, command, offset, data.length);
            }

            // Send command
            Sender jmcSerialSender = new Sender();
            jmcSerialSender.start(optPort, command);
        }
    }

}

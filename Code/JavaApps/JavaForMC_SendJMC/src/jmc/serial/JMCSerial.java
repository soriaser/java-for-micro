package jmc.serial;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.math.BigInteger;

import jssc.SerialPortList;

public class JMCSerial {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // Print ports option requested
        boolean optPrintPorts = false;

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

            byte[] data = new BigInteger(hexStringData, 16).toByteArray();

            JMCSerialSender jmcSerialSender = new JMCSerialSender();
            jmcSerialSender.send(optPort, data);
        }
    }

}

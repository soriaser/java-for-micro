package jmc.serial;

import jssc.SerialPort;
import jssc.SerialPortException;

public class JMCSerialSender {

    private final static byte RX_CONTINUE = (byte) 0x61;
    
    private final static byte RX_WAIT = (byte) 0x60;

    private final static short SW_NO_ERROR = (byte) 0x9000;

    private int BaudRate = 2400;

    public JMCSerialSender() {};

    public void setBaudRate(int baudrate) {
        this.BaudRate = baudrate;
    }

    public void send(String port, byte[] bytes) {
        byte receivedByte = RX_WAIT;
        short statusWord = (short) 0;
        boolean statusWordReceived = false;

        SerialPort serialPort = new SerialPort(port);

        try {
            serialPort.openPort();
            serialPort.setParams(this.BaudRate, 8, 1, 0);

            for (int ii = 0; (ii < bytes.length) && (!statusWordReceived); ii++) {
                // Send one byte
                serialPort.writeByte(bytes[ii]);
                receivedByte = RX_WAIT;

                while (receivedByte != RX_CONTINUE) {
                    byte[] receivedBytes = serialPort.readBytes(1);
                    receivedByte = receivedBytes[0];

                    if ((receivedByte != RX_WAIT) &&
                        (receivedByte != RX_CONTINUE)) {
                        receivedBytes = serialPort.readBytes(1);

                        statusWord  = (short) ((receivedByte << 8) & 0xFF00);
                        statusWord |= (short) (receivedBytes[0] & 0x00FF);

                        statusWordReceived = true;
                        break;
                    }
                }
            }

        } catch (SerialPortException exception) {
            System.out.println(exception);
        }

        System.out.println("Status Word:\n");
        System.out.println(Integer.toHexString(statusWord & 0xFFFF));
    }
}

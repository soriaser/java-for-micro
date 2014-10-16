package jmc.serial;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Timer;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class Sender implements SerialPortEventListener {

    private SerialPort Port = null;

    private byte[] Data = null;

    private int Offset = 0;

    private int BaudRate = 2400;

    private final static byte RX_CONTINUE = (byte) 0x61;

    private final static int TIME = 10000;

    private Timer TimerSend = new Timer(TIME, new ActionListener() {
        
        public void actionPerformed(ActionEvent action) {
            TimerSend.stop();
            sendNext();
        }
    });

    public Sender() {};

    public void setBaudRate(int baudrate) {
        this.BaudRate = baudrate;
    }

    public void sendNext() {
        try {
            // Send next byte
            this.Port.writeByte(this.Data[this.Offset]);
            System.out.println("    ->" +
                    Integer.toHexString((this.Data[this.Offset] & 0xFF)) +
                    "   " +
                    "(" + this.Offset + "/" + this.Data.length + ")"
                    );
            this.Offset++;

            TimerSend.start();
        } catch (SerialPortException e) {
            System.out.println(e);
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void start(String port, byte[] bytes) {
        // New port
        this.Port = new SerialPort(port);
        // Store data to send
        this.Data = new byte[bytes.length + 1];
        System.arraycopy(bytes, (short) 0, this.Data, (short) 0, bytes.length);

        try {
            // Open and configure port
            this.Port.openPort();
            this.Port.setParams(this.BaudRate, 8, 1, 0);
            System.out.println("Sending by " + port + "\n\n");

            // Register as a Listener
            this.Port.setEventsMask(SerialPort.MASK_RXCHAR);
            this.Port.addEventListener(this);

            // Start!
            this.sendNext();
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }

    public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            TimerSend.stop();

            try {
                byte buffer[] = this.Port.readBytes(1);

                System.out.println("    <-" + Integer.toHexString(
                        (buffer[0] & 0xFF)));

                if (buffer[0] == RX_CONTINUE) {
                    this.sendNext();
                } else {
                    // Close port
                    this.Port.closePort();
                }
            }
            catch (SerialPortException ex) {
                System.out.println(ex);
            }
        }
    }
}

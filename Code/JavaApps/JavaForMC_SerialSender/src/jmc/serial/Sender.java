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

    private int BaudRate = 9600;
    
    private byte Retries = 0;

    private final static byte RX_CONTINUE = (byte) 0x61;

    private final static byte MAX_RETRIES = 2;

    private final static int TIME = 1000;

    private Timer TimerSend = new Timer(TIME, new ActionListener() {
        
        public void actionPerformed(ActionEvent action) {
            // Timer triggered, stop it
            TimerSend.stop();

            if (Retries < MAX_RETRIES) {
                // If timer has been triggered means that resend is required.
                // Offset is decreased to resend previous byte
                Offset--;
                // Send again
                sendNext();
                // Increase retries
                Retries++;
            } else {
                System.out.print("\n");
                System.out.print("Retries exceeding!! Port is closed!!\n");

                try {
                    Port.closePort();
                } catch (SerialPortException e) {
                    e.printStackTrace();
                }
            }
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

            // Print bytes
            if (this.Retries == 0) {
                if ((this.Offset % 16) == 0) {
                    System.out.print("\n");
                    System.out.print("-> ");
                }
                System.out.printf("0x%02X ", this.Data[this.Offset]);
            }

            // Increase data offset
            this.Offset++;
            // Start timer to allow resend in case of send error
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
            System.out.println("Start sending by " + port + "\n\n");

            // Register the listener
            this.Port.setEventsMask(SerialPort.MASK_RXCHAR);
            this.Port.addEventListener(this);

            // Start sending first byte
            this.sendNext();
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }

    public void serialEvent(SerialPortEvent event) {
        // If data received...
        if (event.isRXCHAR()) {
            // Stop timer becuase we have received something
            TimerSend.stop();

            try {
                // Read byte received
                byte buffer[] = this.Port.readBytes(1);

                // If byte indicates that we can send next byte, we continue.
                // Otherwise, stop communication.
                if (buffer[0] == RX_CONTINUE) {
                    // Send byte
                    this.sendNext();
                } else {
                    // Print response
                    System.out.print("\n");
                    System.out.printf("<- 0x%02X\n", buffer[0]);
                    // Close port
                    this.Port.closePort();
                }

                // Reset retries
                Retries = 0;
            }
            catch (SerialPortException e) {
                System.out.println(e);
            }
        }
    }
}

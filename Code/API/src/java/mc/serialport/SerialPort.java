package java.mc.serialport;

/**
 * Serial Port receiver and transmitter functionality if microcontroller is
 * connected to required pins.
 *
 * @author Sergio Soria
 * @version 1.0.0
 */
public final class SerialPort {

    /**
     * If byte has been received through Serial Port, it returns the
     * value of it. If byte has not been received,, it returns current value
     * in receive register of microcontroller.
     *
     * @return Received byte value.
     */
    public native static byte Receive();

    /**
     * Sends some data through SerialPort pins if they are connected.
     *
     * @param data Bytes to send.
     * @param offset Offset in byte array where data to send starts.
     * @param length Number of bytes to send.
     */
    public native static void Send(byte[] data, short offset, short length);

}

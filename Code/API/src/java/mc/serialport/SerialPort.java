package java.mc.serialport;

/**
 * Serial Port receiver and transmitter functionality if microcontroller is
 * connected to required pins.
 *
 * Following example shows an echo application.
 *
 * <code>
 * public class MyApplication extends MicroApplication implements
 * SerialPortListener {
 *
 *     private SerialPort m_SerialPort = null;
 *
 *     public void main() throws MicroApplicationException {
 *         // Nothing to do
 *     }
 *
 *     public void onLoad(byte[] data, short offset, short length)
 *          throws MicroApplicationException {
 *         m_SerialPort = SerialPort.getSerialPort();
 *         m_SerialPort.enable();
 *     }
 *
 *     public void onReceive(byte[] data, short offset, short length) {
 *         if (m_SerialPort != null) {
 *             m_SerialPort.send(data, offset, length);
 *         } 
 *     }
 *
 * }
 * </code>
 *
 * @author Sergio Soria
 * @version 1.0.0
 */
public final class SerialPort {

    /**
     * Gets <code>SerialPort</code> object instance.
     *
     * @return <code>SerialPort</code> object instance.
     *
     * @throws MicroApplicationException with following reason codes:
     * <ul>
     * <li><code>MicroApplicationException.UNAVAILABLE_FUNCTIONALITY</code> if
     * it does not support Serial Port receiver or transmitter functionality.
     * </li>
     * </ul> 
     */
    public native static SerialPort getSerialPort();

    /**
     * Enables receive and transmit data functionality.
     */
    public native void enable();

    /**
     * Disables receive and transmit data functionality.
     */
    public native void disable();

    /**
     * Sends some data through SerialPort pins if they are connected.
     *
     * @param data Bytes to send.
     * @param offset Offset in byte array where data to send starts.
     * @param length Number of bytes to send.
     */
    public native void send(byte[] data, short offset, short length);

}

package java.io.serialport;

/**
 * Serial Port listener.
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
public interface SerialPortListener {

    /**
     * It is triggered if Serial Port is enabled and some bytes are received by
     * Rx pin.
     *
     * @param data Bytes received.
     * @param offset Offset in byte array where data received starts.
     * @param length Number of bytes received.
     */
    public void onReceive(byte[] data, short offset, short length);

}

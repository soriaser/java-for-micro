package java.io.serialport;

import java.mc.MicroApplicationException;

/**
 * <code>SerialPortException</code> represents a <code>SerialPort</code> class
 * related exception.
 *
 * @author Sergio Soria
 * @version 1.0.0
 */
public class SerialPortException extends MicroApplicationException {

    /**
     * Reason code to indicate if Serial Port has not been enabled.
     */
    public static short SERIAL_PORT_DISABLED = (short) 0;

    /**
     * Constructs SerialPortException.
     *
     * @param reason The reason for the exception.
     */
    public SerialPortException(short reason) {
        super(reason);
    }
}

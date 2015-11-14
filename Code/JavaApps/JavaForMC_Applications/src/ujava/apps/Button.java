package ujava.apps;

import java.mc.MicroApplication;
import java.mc.MicroApplicationListener;
import java.mc.ports.Port;
import java.mc.ports.PortConstants;
import java.mc.serialport.SerialPort;
import java.mc.serialport.SerialPortConstants;

public class Button extends MicroApplication implements MicroApplicationListener {

    private boolean m_OnReceive = true;
    private boolean m_SendMessage = true;

    private byte[] m_MessageOn  = {'O', 'N'};
    private byte[] m_MessageOff = {'O', 'F', 'F'};
    
    private boolean m_IsLedOn;
    
    private Port m_Port;

    public final static byte LED = (byte) 0x02;


    public void main() {
        m_Port = Port.getPort(PortConstants.PORTB);
        m_Port.setOutputPin(LED);
        m_Port.setPinToZero(LED);

        m_IsLedOn = false;

        MicroApplication.SetEvent(PortConstants.EVENT_INTERRUPT_0);

        if (m_OnReceive) {
            MicroApplication.SetEvent(SerialPortConstants.EVENT_RECEIVED_BYTE);
        }
    }

    public void onEvent(byte event) {
        if (PortConstants.EVENT_INTERRUPT_0 == event) {
            Port port = Port.getPort(PortConstants.PORTB);
    
            if (m_IsLedOn) {
                port.setPinToZero(LED);

                if (m_SendMessage) {
                    SerialPort.Send(m_MessageOn, (short) 0, (short) 2);
                }
            } else {
                port.setPinToOne(LED);
                
                if (m_SendMessage) {
                    SerialPort.Send(m_MessageOff, (short) 0, (short) 3);
                }
            }
    
            m_IsLedOn = !m_IsLedOn;
        }
    }

}

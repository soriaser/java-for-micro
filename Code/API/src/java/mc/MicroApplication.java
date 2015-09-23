package java.mc;

public abstract class MicroApplication {

    /**
     * Constructor.
     */
    protected MicroApplication() {}

    /**
     * Starting point of microcontroller application. After device power up or
     * reset, JVM integrated in device starts running this method.
     */
    public abstract void main();

    /**
     * Some interruptions can happen during life cycle of the device, and it is
     * possible that the application requires to make some process when it this
     * interruption happens. This interruptions are called events in this case.
     * 
     * SetEvent provides a mechanism to register the application to one specific
     * event, while ClearEvent allows to deregister the events. 
     * 
     * @param event
     */
    public static native void ClearEvent(byte event);

    /**
     * Some interruptions can happen during life cycle of the device, and it is
     * possible that the application requires to make some process when it this
     * interruption happens. This interruptions are called events in this case.
     * 
     * This method provides a mechanism to register the application to one
     * specific event. If application requires to be registered to several
     * events, it has to be called several times indicating different events.
     * 
     * If application is registered to some event, it has to implement
     * MicroApplicationListener interface because, if the event happens, onEvent
     * method is called. 
     * 
     * @param event Event to register. Current possible options are:
     * Port.EVENT_INTERRUPT_0,
     * Port.EVENT_INTERRUPT_1 and
     * SerialPort.EVENT_RECEIVED_BYTE
     */
    public static native void SetEvent(byte event);

    /**
     * Sets device in sleep mode during some milliseconds. During this time,
     * the microcontroller is not executing any code.
     *
     * @param milliseconds Number of millisecons to wait.
     */
    public static native void Sleep(short milliseconds);

}

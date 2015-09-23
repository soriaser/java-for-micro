package java.mc.timers;

public final class Timer {

    /**
     * Some microcontrollers integrates several timers to configurate.
     * This method returns a Timer class representing this device resource
     * but allows to specify which timer is going to be requested.
     *
     * @param timer Device timer to be requested. Options can
     * be:
     * TimerConstants.TIMER0 and TimerConstants.TIMER1.
     *
     * @return Timer class representing microcontroller
     * resource.
     */
    public native static Timer getTimer(byte timer);

    /**
     * Clears current value of timer counter register.
     */
    public native void clear();

    /**
     * Disables timer.
     */
    public native void disable();

    /**
     * Enables timer.
     */
    public native void enable();

    /**
     * Reads current value of timer register.
     */
    public native short read();

}

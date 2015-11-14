/*
 * File:   Main.c
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 16:58
 */

#include "Common.h"
#include "Api.h"
#include "JavaClass.h"
#include "JVM.h"
#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"
#include "Timer.h"

void interrupt ISR(void)
{
    if (RCIF) {
        SerialPort_ISR();

        if (1 == Api_EventsRegistered.receive) {
            Api_Events.receive = 1;
        }

        RCIF = 0;
    }

    if (
#if (PLATFORM == PLATFORM_PIC18F4520)
        (INT0IF) &&
#elif (PLATFORM == PLATFORM_PIC16F877)
        (INTF) &&
#endif
        (1 == Api_EventsRegistered.int0)) {
#ifdef STORE_TIMER_IF_INT0
        TMR1ON = 0;
        //Timer_ValueRead = READTIMER1();
#endif // STORE_TIMER_IF_INT0
#if (PLATFORM == PLATFORM_PIC18F4520)
        INT0IF = 0;
#elif (PLATFORM == PLATFORM_PIC16F877)
        INTF = 0;
#endif
        Api_Events.int0 = 1;
    }
}

void main(void)
{
    // Serial Port is allways enabled in order to listen commands
    SerialPort_Init();

    while (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        if (LOADER_STATE_PENDING == Loader_State) {
            Loader_ProcessCommand(SerialPort_CurrentValueRx);
        }
    }

    JavaClass_Init();
    Jvm_Init();
    Jvm_Main();
}

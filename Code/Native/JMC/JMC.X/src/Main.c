/*
 * File:   Main.c
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 16:58
 */

#include "Common.h"

#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"
#include "Timer.h"

void interrupt ISR(void)
{
    if (RCIF) {
        SerialPort_ISR();
    }

    if (TMR0IF) {
        Timer_T0_ISR();
    }
}

void main(void)
{
    if (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        SerialPort_Init();
        Timer_T0_Init();
    }

    while (1) {
        if ((LOADER_ENABLED == Loader_IsLoaderEnabled)
                && (Loader_LoaderState & LOADER_STATE_PENDING)) {
            Loader_ISR();
        }
    }
}

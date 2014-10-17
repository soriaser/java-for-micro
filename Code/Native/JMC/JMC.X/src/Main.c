/*
 * File:   Main.c
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 16:58
 */

#include "Common.h"
#include "JVM.h"
#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"
#include "Timer.h"

void interrupt ISR(void)
{
    if (RCIF) {
        SerialPort_ISR();
    }
}

void main(void)
{
    if (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        SerialPort_Init();
    }

    while (1) {
        if ((LOADER_ENABLED == Loader_IsLoaderEnabled)
                && (LOADER_STATE_PENDING == Loader_State)) {
            Loader_ProcessCommand(SerialPort_CurrentValueRx);
        }

        if (LOADER_DISABLED == Loader_IsLoaderEnabled) {
            Jvm_PreInit();
        }
    }
}

/*
 * File:   Main.c
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 16:58
 */

#include "Common.h"
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
    }
}

void main(void)
{
    if (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        SerialPort_Init();
    }

    while (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        if (LOADER_STATE_PENDING == Loader_State) {
            Loader_ProcessCommand(SerialPort_CurrentValueRx);
        }
    }

    if (LOADER_DISABLED == Loader_IsLoaderEnabled) {
        JavaClass_Init();
        Jvm_Init();
        Jvm_Main();
    }
}

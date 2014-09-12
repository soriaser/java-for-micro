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

    while (1);
}

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

#pragma config OSC = HS

void interrupt ISR(void)
{
    if (RCIF) {
        SerialPort_ISR();
    }
}

void main(void) {

    if (LOADER_ENABLED ==
            Mm_GetByteNVM((unsigned char *) &Loader_IsLoaderEnabled)) {
        SerialPort_Init();
    }

    while (1);
}

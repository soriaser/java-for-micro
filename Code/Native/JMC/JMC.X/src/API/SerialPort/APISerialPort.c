#include "Common.h"
#include "APISerialPort.h"

uint8_t API_SerialPort_Receive(void)
{
    return SerialPort_Receive();
}

void API_SerialPort_Send(uint8_t *data, uint16_t offset, uint16_t size)
{
    for (uint16_t ii = 0; ii < size; ii++) {
        SerialPort_Send(data[offset + ii]);
    }
}

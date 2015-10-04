/* 
 * File:   Port_PIC16F877.h
 * Author: Sergio Soria
 *
 * Created on 25 de abril de 2015, 18:21
 */

#ifndef PORT_PIC16F877_H
#define PORT_PIC16F877_H

#ifdef __cplusplus
extern "C" {
#endif

extern void Port_ClearEvent(uint8_t event);

extern void Port_GetPortRegistry(uint8_t port);

extern void Port_SetEvent(uint8_t event);

extern void Port_SetPin(uint8_t pins, uint8_t type);

#ifdef __cplusplus
}
#endif

#endif /* PORT_PIC16F877_H */


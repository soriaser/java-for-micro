/* 
 * File:   API.h
 * Author: Sergio Soria
 *
 * Created on 30 de diciembre de 2014, 11:49
 */

#ifndef API_H
#define	API_H

#ifdef	__cplusplus
extern "C" {
#endif

#define API_BIT_MASK_NATIVE_METHOD  (uint16_t) 0x8000
#define API_ID_MASK                 0x7F

typedef struct {
  unsigned int0:1;
  unsigned int1:1;
  unsigned receive:1;
} api_events_t;

extern api_events_t Api_Events;

extern api_events_t Api_EventsRegistered;

extern void Api_ExecuteNativeMethod(uint8_t id, uint8_t bytecode);

#ifdef	__cplusplus
}
#endif

#endif	/* API_H */


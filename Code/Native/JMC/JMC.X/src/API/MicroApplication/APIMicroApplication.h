/* 
 * File:   APIMicroAplication.h
 * Author: Sergio Soria
 *
 * Created on 4 de enero de 2015, 20:58
 */

#ifndef APIMICROAPLICATION_H
#define	APIMICROAPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

extern uint8_t Api_MicroApplication_Events;

extern void Api_MicroApplication_SetEvent(uint8_t event);

extern void API_MicroApplication_Sleep(uint16_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* APIMICROAPLICATION_H */

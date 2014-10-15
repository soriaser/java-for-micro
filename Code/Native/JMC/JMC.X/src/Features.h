/* 
 * File:   Features.h
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 17:12
 */

#ifndef FEATURES_H
#define	FEATURES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ 4000000

#define BAUDRATE 2400

#define HEAP_SIZE 1024

#define JMC_CLASSES_BUFFER_SIZE 1
#define JMC_FIELDS_BUFFER_SIZE  300
#define JMC_METHODS_BUFFER_SIZE 100
#define JMC_CODE_BUFFER_SIZE    1000

#define PLATFORM_PIC18F4520 0
#define PLATFORM PLATFORM_PIC18F4520

#ifdef	__cplusplus
}
#endif

#endif	/* FEATURES_H */


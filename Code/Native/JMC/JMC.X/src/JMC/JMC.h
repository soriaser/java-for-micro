/* 
 * File:   JMC.h
 * Author: Sergio Soria
 *
 * Created on 7 de septiembre de 2014, 19:02
 */

#ifndef JMC_H
#define	JMC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Common.h"

#define JMC_TAG_CLASS                       0x80
#define JMC_TAG_FIELDS                      0x81
#define JMC_TAG_METHODS                     0x82
#define JMC_TAG_FIELD                       0xC1
#define JMC_TAG_METHOD                      0xC2

#define JMC_FIELD_BYTES_SIZE    3
#define JMC_METHOD_BYTES_SIZE   6
#define JMC_CLASS_BYTES_SIZE    6

#define JMC_UNDEFINED_1B        0xFF
#define JMC_UNDEFINED_2B        0xFFFF

typedef struct {
    uint8_t id;
    uint16_t value;
} jmc_f;

typedef struct {
    uint16_t id;
    uint16_t size;
    uint16_t offset;
} jmc_m;

typedef struct {
    uint16_t fieldsOffset;
    uint8_t fields;
    uint16_t methodsOffset;
    uint8_t methods;
} jmc_c;

extern NVMDATA uint8_t Jmc_Code[JMC_CODE_BUFFER_SIZE];

extern NVMDATA jmc_f Jmc_Fields[JMC_FIELDS_BUFFER_SIZE];

extern NVMDATA jmc_m Jmc_Methods[JMC_METHODS_BUFFER_SIZE];

extern NVMDATA jmc_c Jmc_Classes[JMC_CLASSES_BUFFER_SIZE];

extern NVMDATA uint16_t Jmc_CurrentOffsetCode;

extern NVMDATA uint16_t Jmc_CurrentOffsetFields;

extern NVMDATA uint16_t Jmc_CurrentOffsetMethods;

extern NVMDATA uint16_t Jmc_CurrentOffsetClasses;

#ifdef	__cplusplus
}
#endif

#endif	/* JMC_H */


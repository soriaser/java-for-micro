/* 
 * File:   JavaClass.h
 * Author: Sergio Soria
 *
 * Created on 18 de octubre de 2014, 11:16
 */

#ifndef JAVACLASS_H
#define	JAVACLASS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct javaclass_class {
  uint8_t super;
  uint8_t fields;
} javaclass_class_t;

typedef struct javaclass_header {
  uint8_t  version;
  uint8_t  methods;
  uint16_t constants;
  uint8_t  classes;
  uint8_t  fields;
  uint8_t  main;
  uint16_t offsetClasses;
  uint16_t offsetConstants;
  uint16_t offsetStrings;
  uint16_t offsetMethods;
} javaclass_header_t;

extern NVMDATA uint16_t JavaClass_DataSize;

extern NVMDATA uint8_t  JavaClass_Data[JAVACLASS_MAX_SIZE_DATA];

#define JavaClass_GetNumberStaticFields() \
    (((javaclass_header_t *) JavaClass_Data)->fields)

extern void JavaClass_Init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* JAVACLASS_H */

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

#define JAVACLASS_METHOD_FLAG_INIT      0x01
#define JAVACLASS_METHOD_FLAG_ONEVENT   0x02

#define JAVACLASS_METHOD_ID_UNKNOWN     0xFFFF

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

typedef struct javaclass_method_header {
    uint16_t code;
    uint16_t id;
    uint8_t  flags;
    uint8_t  arguments;
    uint8_t  locals;
    uint8_t  stack;
} javaclass_method_header_t;

extern NVMDATA uint16_t JavaClass_DataSize;

extern NVMDATA uint8_t  JavaClass_Data[JAVACLASS_MAX_SIZE_DATA];

#define JavaClass_GetOffsetMethods() \
    (Mm_GetU16((uint32_t) &((javaclass_header_t *) \
        JavaClass_Data)->offsetMethods))

#define JavaClass_GetNumberConstants() \
    (Mm_GetU16((uint32_t) &((javaclass_header_t *) JavaClass_Data)->constants))

#define JavaClass_GetNumberStaticFields() \
    (Mm_GetU08((uint32_t) &((javaclass_header_t *) JavaClass_Data)->fields))

#define JavaClass_GetNumberMethods() \
    (Mm_GetU08((uint32_t) &((javaclass_header_t *) JavaClass_Data)->methods))

#define JavaClass_GetMainMethodIndex() \
    (Mm_GetU08((uint32_t) &((javaclass_header_t *) JavaClass_Data)->main))

#define JavaClass_GetMethod(index) \
    ((javaclass_method_header_t *) (JavaClass_Data + \
    JavaClass_GetOffsetMethods() + (sizeof(javaclass_method_header_t) * index)))

#define JavaClass_GetVersion() \
    (Mm_GetU08((uint32_t) &((javaclass_header_t *) JavaClass_Data)->version))

extern uint16_t JavaClass_GetOnEventIndex(void);

extern void JavaClass_Init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* JAVACLASS_H */

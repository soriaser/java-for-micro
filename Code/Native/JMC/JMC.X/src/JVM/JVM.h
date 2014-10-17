/* 
 * File:   JVM.h
 * Author: Sergio Soria
 *
 * Created on 30 de septiembre de 2014, 18:29
 */

#ifndef JVM_H
#define	JVM_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t  version;
  uint8_t  methods;
  uint16_t main;
  uint16_t offsetConstants;
} jvm_header_t;

extern NVMDATA uint16_t Jvm_ClassDataSize;

extern NVMDATA uint8_t  Jvm_ClassData[JVM_MAX_SIZE_CLASS_DATA];

extern void Jvm_PreInit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* JVM_H */


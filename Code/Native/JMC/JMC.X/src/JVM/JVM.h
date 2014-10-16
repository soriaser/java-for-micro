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

extern NVMDATA uint16_t Jvm_ClassDataSize;

extern NVMDATA uint8_t  Jvm_ClassData[JVM_MAX_SIZE_CLASS_DATA];

#ifdef	__cplusplus
}
#endif

#endif	/* JVM_H */


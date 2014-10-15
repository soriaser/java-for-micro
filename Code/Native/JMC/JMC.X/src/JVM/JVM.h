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

#define BC_ALOAD_0          0x2A
#define BC_ALOAD_1          0x2B
#define BC_ALOAD_2          0x2C
#define BC_ALOAD_3          0x2D

extern void Jvm_Init(void);
extern void Jvm_ExecuteMethod(uint16_t jmcClassOffset, uint16_t jmcMethodId);

#ifdef	__cplusplus
}
#endif

#endif	/* JVM_H */


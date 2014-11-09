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

#define BC_ILOAD        0x15
#define BC_ILOAD_0      0x1A
#define BC_ILOAD_1      0x1B
#define BC_ILOAD_2      0x1C
#define BC_ILOAD_3      0x1D
#define BC_IRETURN      0xAC
#define BC_RETURN       0xB1

extern void Jvm_Init(void);

extern void Jvm_Main(void);

extern void Jvm_RunMethod(javaclass_method_header_t *method);

#ifdef	__cplusplus
}
#endif

#endif	/* JVM_H */


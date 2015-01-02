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

#define BC_ICONST_M1        0x02
#define BC_ICONST_0         0x03
#define BC_ICONST_1         0x04
#define BC_ICONST_2         0x05
#define BC_ICONST_3         0x06
#define BC_ICONST_4         0x07
#define BC_ICONST_5         0x08
#define BC_ILOAD            0x15
#define BC_ILOAD_0          0x1A
#define BC_ILOAD_1          0x1B
#define BC_ILOAD_2          0x1C
#define BC_ILOAD_3          0x1D
#define BC_ISTORE_0         0x3B
#define BC_ISTORE_1         0x3C
#define BC_ISTORE_2         0x3D
#define BC_ISTORE_3         0x3E
#define BC_IRETURN          0xAC
#define BC_RETURN           0xB1
#define BC_PUTFIELD         0xB5
#define BC_INVOKESPECIAL    0xB7

extern void Jvm_Init(void);

extern void Jvm_Main(void);

extern void Jvm_RunMethod(uint16_t index);

#ifdef	__cplusplus
}
#endif

#endif	/* JVM_H */


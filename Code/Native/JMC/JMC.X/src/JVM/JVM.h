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

#define BC_NOP              0x00
#define BC_ICONST_M1        0x02
#define BC_ICONST_0         0x03
#define BC_ICONST_1         0x04
#define BC_ICONST_2         0x05
#define BC_ICONST_3         0x06
#define BC_ICONST_4         0x07
#define BC_ICONST_5         0x08
#define BC_BIPUSH           0x10
#define BC_SIPUSH           0x11
#define BC_ILOAD            0x15
#define BC_ILOAD_0          0x1A
#define BC_ILOAD_1          0x1B
#define BC_ILOAD_2          0x1C
#define BC_ILOAD_3          0x1D
#define BC_ISTORE_0         0x3B
#define BC_ISTORE_1         0x3C
#define BC_ISTORE_2         0x3D
#define BC_ISTORE_3         0x3E
#define BC_BASTORE          0x54
#define BC_DUP              0x59
#define BC_IADD             0x60
#define BC_ISUB             0x64
#define BC_IMUL             0x68
#define BC_IDIV             0x6C
#define BC_IREM             0x70
#define BC_INEG             0x74
#define BC_ISHL             0x78
#define BC_ISHR             0x7A
#define BC_IUSHR            0x7C
#define BC_IAND             0x7E
#define BC_IOR              0x80
#define BC_IXOR             0x82
#define BC_IINC             0x84
#define BC_IFEQ             0x99
#define BC_IFNE             0x9A
#define BC_IFLT             0x9B
#define BC_IFGE             0x9C
#define BC_IFGT             0x9D
#define BC_IFLE             0x9E
#define BC_IF_ICMPEQ        0x9F
#define BC_IF_ICMPNE        0xA0
#define BC_IF_ICMPLT        0xA1
#define BC_IF_ICMPGE        0xA2
#define BC_IF_ICMPGT        0xA3
#define BC_IF_ICMPLE        0xA4
#define BC_GOTO             0xA7
#define BC_IRETURN          0xAC
#define BC_RETURN           0xB1
#define BC_GETSTATIC        0xB2
#define BC_PUTSTATIC        0xB3
#define BC_GETFIELD         0xB4
#define BC_PUTFIELD         0xB5
#define BC_INVOKEVIRTUAL    0xB6
#define BC_INVOKESPECIAL    0xB7
#define BC_INVOKESTATIC     0xB8
#define BC_NEWARRAY         0xBC

extern void Jvm_Init(void);

extern void Jvm_Main(void);

extern void Jvm_RunMethod(uint16_t index);

#ifdef	__cplusplus
}
#endif

#endif	/* JVM_H */

/* 
 * File:   Stack.h
 * Author: Sergio Soria
 *
 * Created on 15 de octubre de 2014, 13:39
 */

#ifndef STACK_H
#define	STACK_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef uint16_t stack_slot_t;

extern uint16_t *Stack_Pointer;

extern uint16_t *Stack_CurrentPointer;

extern uint16_t *Stack_BasePointer;

#define Stack_Add(value) \
    (Stack_CurrentPointer += (int8_t) value)

#define Stack_IsEmpty() \
    (Stack_CurrentPointer == Stack_BasePointer)    

#define Stack_Pop() \
    (*(Stack_CurrentPointer--))

extern void Stack_Init(void);

extern uint8_t Stack_IsIdInUse(uint16_t id);

extern void Stack_Push(uint16_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* STACK_H */


/* 
 * File:   Heap.h
 * Author: Sergio Soria
 *
 * Created on 30 de septiembre de 2014, 18:33
 */

#ifndef HEAP_H
#define	HEAP_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef uint8_t heap_id_t;

extern uint8_t Heap[JVM_MAX_SIZE_HEAP];

extern void Heap_Init(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HEAP_H */


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

typedef struct {
  uint8_t  id;
  uint8_t  ref;
  uint16_t size;
} heap_t;

extern uint8_t Heap[JVM_MAX_SIZE_HEAP];

extern uint8_t Heap_Alloc(uint8_t ref, uint16_t size);

extern void    Heap_GetBytes(uint16_t bytes);

extern heap_t *Heap_GetHeader(uint8_t id);

extern void   *Heap_GetHeaderAddress(uint8_t id);

extern uint8_t Heap_GetNewId(void);

extern void    Heap_Init(void);

extern void    Heap_SetBytes(uint16_t bytes);

#ifdef	__cplusplus
}
#endif

#endif	/* HEAP_H */


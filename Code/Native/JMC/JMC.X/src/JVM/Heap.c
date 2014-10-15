#include "Common.h"

#include "Heap.h"

#define HEAP_ID_FREE 0

uint8_t Heap[1024];

typedef struct {
  heap_id_t id;
  uint16_t fieldRef;
  uint16_t size;
} heap_t;

void Heap_Init(void)
{
  heap_t *ptrHeap = (heap_t *) &Heap[0];
  ptrHeap->id  = HEAP_ID_FREE;
  ptrHeap->size = sizeof(Heap) - sizeof(heap_t);
}

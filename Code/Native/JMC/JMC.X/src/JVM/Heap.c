#include "Common.h"
#include "Heap.h"

#define HEAP_ID_FREE 0

uint8_t  Heap[JVM_MAX_SIZE_HEAP];
uint16_t Heap_BaseOffset = 0;

void Heap_Init(void)
{
    heap_t *heap = (heap_t *) &Heap[0];
    heap->id  = HEAP_ID_FREE;
    heap->size = sizeof(Heap) - sizeof(heap_t);
}

void Heap_GetBytes(uint16_t bytes)
{
    heap_t *heap = (heap_t *) &Heap[Heap_BaseOffset];
    uint16_t size = heap->size;

    // TODO: Check size

    Heap_BaseOffset += bytes;
    heap = (heap_t *) &Heap[Heap_BaseOffset];
    heap->id = HEAP_ID_FREE;
    heap->size = size - bytes;
}

heap_t *Heap_GetHeader(uint8_t id)
{
    uint16_t offset = Heap_BaseOffset;

    while (offset < sizeof(Heap)) {
        heap_t *heap = (heap_t *) &Heap[offset];

        if (heap->id == id) {
            return heap;
        }

        offset += heap->size + sizeof(heap_t);
    }

    return NULL;
}

void *Heap_GetHeaderAddress(uint8_t id)
{
    heap_t *heap = Heap_GetHeader(id);

    if (heap == NULL) {
        EndlessLoop();
    }

    return (heap + 1);
}

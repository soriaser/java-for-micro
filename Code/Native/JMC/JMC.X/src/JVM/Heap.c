#include "Common.h"
#include "Heap.h"
#include "Stack.h"
#include "MemoryManagement.h"

#define HEAP_ID_FREE 0

uint8_t  Heap[JVM_MAX_SIZE_HEAP];
uint16_t Heap_BaseOffset = 0;

void Heap_Init(void)
{
    heap_t *heap = (heap_t *) &Heap[0];
    heap->id  = HEAP_ID_FREE;
    heap->size = sizeof(Heap) - sizeof(heap_t);
}

uint8_t Heap_IsIdInUse(uint16_t id)
{
    heap_t *heap = NULL;
    uint16_t offset = Heap_BaseOffset;

    while (offset < sizeof(Heap)) {
        heap = (heap_t *) &Heap[offset];

        if (heap->ref) {
            uint8_t ii = 0;

            for (;ii < (heap->size / sizeof(uint16_t)); ii++) {
                if (((uint16_t *) (heap + 1))[ii] == id) {
                    return 0x01;
                }
            }
        }

        offset += heap->size + sizeof(heap_t);
    }

    return 0x00;
}

void Heap_GarbageCollect(void)
{
    heap_t *heap = NULL;
    uint16_t size = 0;
    uint16_t offset = Heap_BaseOffset;

    while (offset < sizeof(Heap)) {
        heap = (heap_t *) &Heap[offset];
        size = heap->size + sizeof(heap_t);

        if (HEAP_ID_FREE != heap->id) {
            if ((!Stack_IsIdInUse(heap->id)) && (!Heap_IsIdInUse(heap->id))) {
                Mm_CopyRam((Heap + Heap_BaseOffset + size),
                        (Heap + Heap_BaseOffset), (offset - Heap_BaseOffset));

                heap = (heap_t *) &Heap[Heap_BaseOffset];
                heap->size += size;
            }
        }

        offset += size;
    }

    if (offset != sizeof(Heap)) {
        EndlessLoop();
    }
}

void Heap_GetBytes(uint16_t bytes)
{
    heap_t *heap = (heap_t *) &Heap[Heap_BaseOffset];
    uint16_t size = heap->size;

    if (size < bytes) {
        Heap_GarbageCollect();
    }

    size = heap->size;

    if ((size < bytes) || (HEAP_ID_FREE != heap->id)) {
        EndlessLoop();
    }

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

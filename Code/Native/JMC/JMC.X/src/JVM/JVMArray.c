#include "Common.h"
#include "Heap.h"
#include "JVMArray.h"

uint8_t JvmArray_New(uint16_t size, uint8_t type)
{
    uint8_t id = Heap_Alloc(0x00, (1 + size * sizeof(uint8_t)));
    uint8_t *ptr = (uint8_t *) Heap_GetHeaderAddress(id);
    ptr[sizeof(heap_t)] = type;
    return id;
}

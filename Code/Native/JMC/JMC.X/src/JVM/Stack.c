#include "Common.h"
#include "Heap.h"
#include "JavaClass.h"
#include "Stack.h"
#include "MemoryManagement.h"

stack_slot_t *Stack_Pointer;
stack_slot_t *Stack_CurrentPointer;
stack_slot_t *Stack_BasePointer;

void Stack_Init(void)
{
    Stack_Pointer = (stack_slot_t *) Heap;
    Stack_CurrentPointer = Stack_Pointer + JavaClass_GetNumberStaticFields();
    Stack_CurrentPointer--;
    Heap_GetBytes(sizeof(stack_slot_t) * JavaClass_GetNumberStaticFields());
}

/*
uint8_t Stack_IsIdInUse(uint16_t id)
{
    uint16_t ii = 0;

    for (;ii < (Stack_CurrentPointer - Stack_Pointer + 1); ii++) {
        if (Stack_Pointer[ii] == id) {
            return 0x01;
        }
    }

    return 0x00;
}
*/

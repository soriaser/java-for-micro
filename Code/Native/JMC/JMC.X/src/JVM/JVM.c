#include "Common.h"
#include "Heap.h"
#include "JVM.h"
#include "Stack.h"

void Jvm_Init(void)
{
    Heap_Init();
    Stack_Init();
    Stack_Push(0);
}

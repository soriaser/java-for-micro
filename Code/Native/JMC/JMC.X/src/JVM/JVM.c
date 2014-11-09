#include "Common.h"
#include "Heap.h"
#include "JavaClass.h"
#include "JVM.h"
#include "MemoryManagement.h"
#include "Stack.h"

uint16_t *localVariables;

void Jvm_Init(void)
{
    Heap_Init();
    Stack_Init();
    Stack_Push(0);
}

void Jvm_Main(void)
{
    uint8_t index = 0;
    javaclass_method_header_t *method;

    // Before to call main method, it is required to call init
    // init method
    for (;index < JavaClass_GetNumberMethods(); index++) {
        method = JavaClass_GetMethod(index);
        if (method->flags & JAVACLASS_METHOD_FLAG_INIT) {
            Jvm_RunMethod(method);
        }
    }

    // Get Main method
    method = JavaClass_GetMethod(JavaClass_GetMainMethodIndex());
    Jvm_RunMethod(method);
}

void Jvm_RunMethod(javaclass_method_header_t *methodHeader)
{
    uint8_t *pc;
    uint8_t  pcIncrement;
    uint8_t  bytecode;

    // Copy of method header in RAM
    javaclass_method_header_t method;

    // Load method header into RAM in order to improve performance
    Mm_ReadNVM((uint32_t) methodHeader, sizeof(javaclass_method_header_t),
            (uint8_t *) &method);

    // Get address to the method code
    pc = (uint8_t *) methodHeader + method.code;

    // Reserve space for locals, stack and arguments
    Heap_GetBytes(sizeof(uint16_t) * (method.locals + method.stack +
            method.arguments));
    localVariables = Stack_CurrentPointer + 1;
    Stack_CurrentPointer += method.locals;
    Stack_BasePointer = Stack_CurrentPointer;

    // Loop to execute and process every bytecode
    do {
        bytecode = (*pc);
        pcIncrement = 1;
        pc += pcIncrement;

        switch (bytecode) {
            case BC_ILOAD_0:
            case BC_ILOAD_1:
            case BC_ILOAD_2:
            case BC_ILOAD_3:
                Stack_Push(localVariables[bytecode - BC_ILOAD_0]);
                break;
        }
    } while((bytecode != BC_IRETURN) && (bytecode != BC_RETURN));
}

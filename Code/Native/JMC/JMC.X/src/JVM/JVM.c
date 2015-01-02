#include "Common.h"
#include "API.h"
#include "Heap.h"
#include "JavaClass.h"
#include "JVM.h"
#include "MemoryManagement.h"
#include "Stack.h"

#define BIT_MASK_NATIVE_METHOD (uint16_t) 0x8000

uint16_t *localVariables;

typedef union {
  uint16_t word;

  struct {
    uint8_t byte_l;
    uint8_t byte_h;
  };

} ushort_t;

void Jvm_Init(void)
{
    Heap_Init();
    Stack_Init();
    Stack_Push(0);
}

void Jvm_Main(void)
{
    uint8_t flags = 0;
    uint8_t index = 0;
    javaclass_method_header_t *method;

    // Before to call main method, it is required to call init
    // init method
    for (;index < JavaClass_GetNumberMethods(); index++) {
        method = JavaClass_GetMethod(index);
        flags = (Mm_GetU08((uint32_t) &((javaclass_method_header_t *)
                method)->flags));

        if (flags & JAVACLASS_METHOD_FLAG_INIT) {
            Jvm_RunMethod(method);
        }
    }

    // Get Main method
    method = JavaClass_GetMethod(JavaClass_GetMainMethodIndex());
    Jvm_RunMethod(method);
}

void Jvm_RunMethod(javaclass_method_header_t *methodHeader)
{
    uint8_t  pcIncrement;
    uint8_t  bytecode;
    ushort_t nextcodes;
    uint16_t tmp;
    uint32_t pc;

    // Copy of method header in RAM
    javaclass_method_header_t method;

    // Load method header into RAM in order to improve performance
    Mm_ReadNVM((uint32_t) methodHeader, sizeof(javaclass_method_header_t),
            (uint8_t *) &method);

    // Get address to the method code
    pc = (uint32_t) (JavaClass_Data + method.code);

    // Reserve space for locals, stack and arguments
    Heap_GetBytes(sizeof(uint16_t) * (method.locals + method.stack +
            method.arguments));
    localVariables = Stack_CurrentPointer + 1;
    Stack_CurrentPointer += method.locals;
    Stack_BasePointer = Stack_CurrentPointer;

    // Loop to execute and process every bytecode
    do {
        bytecode = Mm_GetU08(pc);

        nextcodes.byte_h = Mm_GetU08(pc + 1);
        nextcodes.byte_l = Mm_GetU08(pc + 2);

        pcIncrement = 1;

        switch (bytecode) {
            case BC_ICONST_M1:
            case BC_ICONST_0:
            case BC_ICONST_1:
            case BC_ICONST_2:
            case BC_ICONST_3:
            case BC_ICONST_4:
            case BC_ICONST_5:
                Stack_Push(bytecode - BC_ICONST_0);
                break;
            case BC_ILOAD_0:
            case BC_ILOAD_1:
            case BC_ILOAD_2:
            case BC_ILOAD_3:
                Stack_Push(localVariables[bytecode - BC_ILOAD_0]);
                break;
            case BC_PUTFIELD:
                tmp = Stack_Pop();
                ((uint32_t *) Heap_GetHeaderAddress(Stack_Pop()))
                        [1 + nextcodes.word] = tmp;
                pcIncrement = 3;
                break;
            case BC_INVOKESPECIAL:
                if ((nextcodes.word & BIT_MASK_NATIVE_METHOD) == 0) {
                    // TODO: execute not native method
                } else {
                    Api_ExecuteNativeMethod(nextcodes.byte_h & API_ID_MASK);
                }

                pcIncrement = 3;
                break;
        }

        pc += pcIncrement;

    } while((bytecode != BC_IRETURN) && (bytecode != BC_RETURN));
}

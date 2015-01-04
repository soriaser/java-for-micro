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
            Jvm_RunMethod(index);
            break;
        }
    }

    // Execute onLoad and Main method
    Jvm_RunMethod(JavaClass_GetOnLoadMethodIndex());
    Jvm_RunMethod(JavaClass_GetMainMethodIndex());
}

void Jvm_RunMethod(uint16_t index)
{
    uint8_t  pcIncrement;
    uint8_t  bytecode;
    ushort_t nextcodes;
    uint16_t aux1;
    uint16_t aux2;
    uint32_t pc;

    javaclass_method_header_t *method_ptr;
    javaclass_method_header_t  method;

    method_ptr = JavaClass_GetMethod(index);
    // Load method header into RAM in order to improve performance
    Mm_ReadNVM((uint32_t) method_ptr, sizeof(javaclass_method_header_t),
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

        nextcodes.byte_l = Mm_GetU08(pc + 1);
        nextcodes.byte_h = Mm_GetU08(pc + 2);

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
            case BC_SIPUSH:
                Stack_Push(nextcodes.word);
                pcIncrement = 3;
                break;
            case BC_ILOAD_0:
            case BC_ILOAD_1:
            case BC_ILOAD_2:
            case BC_ILOAD_3:
                Stack_Push(localVariables[bytecode - BC_ILOAD_0]);
                break;
            case BC_ISTORE_0:
            case BC_ISTORE_1:
            case BC_ISTORE_2:
            case BC_ISTORE_3:
                localVariables[bytecode - BC_ISTORE_0] = Stack_Pop();
                break;
            case BC_IFEQ:
            case BC_IFNE:
            case BC_IFLT:
            case BC_IFGE:
            case BC_IFGT:
            case BC_IFLE:
            case BC_IF_ICMPEQ:
            case BC_IF_ICMPNE:
            case BC_IF_ICMPLT:
            case BC_IF_ICMPGE:
            case BC_IF_ICMPGT:
            case BC_IF_ICMPLE:
                if ((BC_IFLE >= bytecode) && (BC_IFEQ <= bytecode)) {
                    aux2 = 0;
                    bytecode -= BC_IFEQ - BC_IF_ICMPEQ;
                } else {
                    aux2 = Stack_Pop();
                }

                aux1 = Stack_Pop();

                switch (bytecode) {
                    case BC_IF_ICMPEQ:
                        aux1 = (aux1 == aux2);
                        break;
                    case BC_IF_ICMPNE:
                        aux1 = (aux1 != aux2);
                        break;
                    case BC_IF_ICMPLT:
                        aux1 = (aux1 < aux2);
                        break;
                    case BC_IF_ICMPGE:
                        aux1 = (aux1 >= aux2);
                        break;
                    case BC_IF_ICMPGT:
                        aux1 = (aux1 > aux2);
                        break;
                    case BC_IF_ICMPLE:
                        aux1 = (aux1 >= aux2);
                        break;
                }

                if (aux1) {
                    pc += nextcodes.word;
                    pcIncrement = 0;
                } else {
                    pcIncrement = 3;
                }
                break;
            case BC_GOTO:
                pc += nextcodes.word - 3;
                pcIncrement = 3;
                break;
            case BC_GETFIELD:
                Stack_Push(((uint32_t *) Heap_GetHeaderAddress(Stack_Pop()))
                        [1 + nextcodes.word]);
                pcIncrement = 3;
                break;
            case BC_PUTFIELD:
                aux1 = Stack_Pop();
                ((uint32_t *) Heap_GetHeaderAddress(Stack_Pop()))
                        [1 + nextcodes.word] = aux1;
                pcIncrement = 3;
                break;
            case BC_INVOKESPECIAL:
            case BC_INVOKESTATIC:
                if ((nextcodes.word & BIT_MASK_NATIVE_METHOD) == 0) {
                    // Store offset to current method bytecode
                    aux1 = (uint16_t) pc - (uint16_t) JavaClass_Data;
                    // Get pointer and method to call
                    method_ptr = JavaClass_GetMethod(nextcodes.word);
                    Mm_ReadNVM((uint32_t) method_ptr,
                        sizeof(javaclass_method_header_t), (uint8_t *) &method);

                    Stack_Add(-method.arguments);
                    aux2 = Stack_CurrentPointer - localVariables;
                    localVariables = Stack_CurrentPointer + 1;

                    Heap_GetBytes(sizeof(uint16_t) * (method.locals + method.stack +
                        method.arguments + 3));

                    Stack_Add(method.locals);
                    Stack_Push(aux1);
                    Stack_Push(index);
                    Stack_Push(aux2);

                    index = nextcodes.word;
                    pc = (uint32_t) (JavaClass_Data + method.code);
                    pcIncrement = 0;
                } else {
                    Api_ExecuteNativeMethod(nextcodes.byte_l & API_ID_MASK);
                    pcIncrement = 3;
                }
                break;
        }

        pc += pcIncrement;

    } while((bytecode != BC_IRETURN) && (bytecode != BC_RETURN));
}

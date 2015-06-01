#include "Common.h"
#include "API.h"
#include "Heap.h"
#include "JavaClass.h"
#include "JVM.h"
#include "JVMArray.h"
#include "MemoryManagement.h"
#include "Stack.h"
#include "APIPortRegistry.h"
#include "APISerialPort.h"

#define JVM_RETURN_INFO_STACK_SIZE 3

stack_slot_t *localVariables;

uint8_t triggeredEvent = 0x00;

void Jvm_Init(void)
{
    Heap_Init();
    Stack_Init();
}

void Jvm_Main(void)
{
    uint8_t flags = 0x00;
    uint8_t index = 0x00;
    uint8_t event = 0x00;

    // Before to call main method, it is required to call init
    // init method
    for (;index < JavaClass_GetNumberMethods(); index++) {
        // Get class flags
        flags = (Mm_GetU08((mm_address_t) &((javaclass_method_header_t *)
                JavaClass_GetMethod(index))->flags));
        // Check if method is <init> or <cinit>
        if ((flags & JAVACLASS_METHOD_FLAG_INIT) ||
                (flags & JAVACLASS_METHOD_FLAG_CLINIT)) {
            Jvm_RunMethod(index);

            if (flags & JAVACLASS_METHOD_FLAG_INIT) {
                break;
            }
        }
    }

    // Execute Main method
    Jvm_RunMethod(JavaClass_GetMainMethodIndex());

    // If no more to execute, endless loop waiting for event
    while (0x01) {
        triggeredEvent = 0x00;

        if (1 == Api_Events.int0) {
            Api_Events.int0 = 0;
            triggeredEvent = API_PORTREGISTRY_EVENT_INT0;
        } else if (1 == Api_Events.receive) {
            Api_Events.receive = 0;
            triggeredEvent = API_SERIALPORT_EVENT_RECEIVED_BYTE;
        }

        if (triggeredEvent > 0x00) {
            Jvm_RunMethod(JavaClass_GetOnEventIndex());
        }
    }
}

void Jvm_RunMethod(uint16_t index)
{
    uint8_t increment;
    uint8_t bytecode;
    word_t  nextcodes;
    int16_t aux1;
    int16_t aux2;
    mm_address_t pc;

    // Method header pointer and struct
    javaclass_method_header_t *method_ptr;
    javaclass_method_header_t  method;

    // Get pointer to current method
    method_ptr = JavaClass_GetMethod(index);
    // Load method header into RAM
    Mm_ReadNVM((mm_address_t) method_ptr, sizeof(javaclass_method_header_t),
            (uint8_t *) &method);

    // Get address to the method code
    pc = (mm_address_t) (JavaClass_Data + method.code);

    // Reserve space for locals, stack and arguments
    Heap_GetBytes(sizeof(stack_slot_t) * (method.locals + method.stack +
            method.arguments));
    // Establish pointers
    localVariables = Stack_CurrentPointer + 1;
    Stack_Add(method.locals);
    Stack_BasePointer = Stack_CurrentPointer;

    // If onEvent method is being executed
    if (JavaClass_GetOnEventIndex() == index) {
        localVariables[1] = triggeredEvent;
    }

    // Loop to execute and process every bytecode
    do {
        // Get bytecode and set next increment as one by default
        bytecode = Mm_GetU08(pc);
        increment = 1;

        // Store two next bytecodes
        nextcodes.byte_l = Mm_GetU08((mm_address_t) (pc + 1));
        nextcodes.byte_h = Mm_GetU08((mm_address_t) (pc + 2));

        // Process bytecode
        switch (bytecode) {
            case BC_NOP:
                break;
            case BC_ICONST_M1:
            case BC_ICONST_0:
            case BC_ICONST_1:
            case BC_ICONST_2:
            case BC_ICONST_3:
            case BC_ICONST_4:
            case BC_ICONST_5:
                Stack_Push(bytecode - BC_ICONST_0);
                break;
            case BC_BIPUSH:
                Stack_Push((0x00FF & nextcodes.byte_l));
                increment = 2;
                break;
            case BC_SIPUSH:
                Stack_Push(nextcodes.word);
                increment = 3;
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
            case BC_BASTORE:
                aux2 = Stack_Pop();
                aux1 = Stack_Pop();
                uint8_t *ptr = (uint8_t *) Heap_GetHeaderAddress(Stack_Pop())
                        + sizeof(heap_t) + 1;
                ptr[aux1] = aux2;
                break;
            case BC_DUP:
                Stack_Push(Stack_CurrentPointer[0]);
                break;
            case BC_IINC:
                localVariables[nextcodes.byte_l] += (nextcodes.byte_h & 0x00FF);
                increment = 3;
                break;
            case BC_IADD:
            case BC_ISUB:
            case BC_IMUL:
            case BC_IDIV:
            case BC_IREM:
            case BC_ISHL:
            case BC_ISHR:
            case BC_IUSHR:
            case BC_IAND:
            case BC_IOR:
            case BC_IXOR:
                aux1 = Stack_Pop();
                aux2 = Stack_Pop();

                switch (bytecode) {
                    case BC_IADD:
                        aux2 += aux1;
                        break;
                    case BC_ISUB:
                        aux2 -= aux1;
                        break;
                    case BC_IMUL:
                        aux2 *= aux1;
                        break;
                    case BC_IDIV:
                        aux2 /= aux1;
                        break;
                    case BC_IREM:
                        aux2 %= aux1;
                        break;
                    case BC_ISHL:
                        aux2 <<= aux1;
                        break;
                    case BC_ISHR:
                        aux2 >>= aux1;
                        break;
                    case BC_IUSHR:
                        aux2 = aux2 >> aux1;
                        break;
                    case BC_IAND:
                        aux2 &= aux1;
                        break;
                    case BC_IOR:
                        aux2 |= aux1;
                        break;
                    case BC_IXOR:
                        aux2 ^= aux1;
                        break;
                }

                Stack_Push(aux2);
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
                    increment = 0;
                } else {
                    increment = 3;
                }
                break;
            case BC_GOTO:
                pc += nextcodes.word - 3;
                increment = 3;
                break;
            /*
            case BC_TABLESWITCH:
                aux1  = (uint16_t)
                        ((Mm_GetU08((mm_address_t) (pc + 7)) << 8) & 0xFF00);
                aux1 |= (uint16_t)
                        (Mm_GetU08((mm_address_t) (pc + 8)) & 0x00FF);

                aux2  = (uint16_t)
                        ((Mm_GetU08((mm_address_t) (pc + 11)) << 8) & 0xFF00);
                aux2 |= (uint16_t)
                        (Mm_GetU08((mm_address_t) (pc + 12)) & 0x00FF);

                nextcodes.word = Stack_Pop();

                if ((nextcodes.word < aux1) || (nextcodes.word > aux2)) {
                    aux2 = 3;
                } else {
                    aux2 = 3 + 12 + ((nextcodes.word - aux1));
                }

                aux1  = (uint16_t)
                        ((Mm_GetU08((mm_address_t) (pc + aux2)) << 8) & 0xFF00);
                aux1 |= (uint16_t)
                        (Mm_GetU08((mm_address_t) (pc + aux2 + 1)) & 0x00FF);
                increment = aux1;
                break;
            case BC_LOOKUPSWITCH:
                nextcodes.word = 1 + 4;
                uint8_t size = Mm_GetU08((mm_address_t) (pc
                        + nextcodes.word + 3));
                nextcodes.word += 4;

                aux1 = Stack_Pop();

                while (size) {
                    if ((Mm_GetU08((mm_address_t) (pc + nextcodes.word + 2)) == aux1 >> 8)
                            && (Mm_GetU08((mm_address_t) (pc + nextcodes.word + 2)) == aux1 >> 0)) {
                        nextcodes.word += 4;
                    }
                    nextcodes.word += 8;
                    size--;
                }

                if (0 == size) {
                    nextcodes.word = 1;
                }

                aux1  = (uint16_t)
                        ((Mm_GetU08((mm_address_t) (pc + nextcodes.word + 2)) << 8) & 0xFF00);
                aux1 |= (uint16_t)
                        (Mm_GetU08((mm_address_t) (pc + nextcodes.word + 3)) & 0x00FF);
                increment = aux1;
                break;
            */
            case BC_IRETURN:
                aux1 = Stack_Pop();
            case BC_RETURN:
                // Check if stack is empty. If stack is empty, it means that it
                // is the last return, otherwise it is required to return to
                // previous code
                if (!Stack_IsEmpty()) {
                    uint8_t  locals  = method.locals;
                    uint8_t  recover = method.locals + method.stack +
                        method.arguments + JVM_RETURN_INFO_STACK_SIZE;

                    // Get offset to local variable offset stored before
                    // call this method
                    uint16_t offset = Stack_Pop();
                    // Recover index of previous method
                    index = Stack_Pop();
                    // Recover previous method
                    method_ptr = JavaClass_GetMethod(index);
                    Mm_ReadNVM((mm_address_t) method_ptr,
                        sizeof(javaclass_method_header_t), (uint8_t *) &method);
                    // Recover program counter to bytecode of previous method
                    pc = (mm_address_t) (JavaClass_Data + Stack_Pop());
                    increment = 3;

                    // Restore local variables pointer
                    Stack_Add(-locals);
                    localVariables = Stack_CurrentPointer - offset;
                    // Restore heap status
                    Heap_SetBytes(sizeof(stack_slot_t) * recover);

                    // If method returns some value, it is pushed into stack
                    if (BC_IRETURN == bytecode) {
                        Stack_Push(aux1);
                    }

                    bytecode = BC_NOP;
                }
                break;
            case BC_GETSTATIC:
                Stack_Push(Stack_Pointer[nextcodes.word]);
                increment = 3;
                break;
            case BC_PUTSTATIC:
                Stack_Pointer[nextcodes.word] = Stack_Pop();
                increment = 3;
                break;
            case BC_GETFIELD:
                aux1 = Stack_Pop();
                Stack_Push(
                        ((stack_slot_t *) Heap_GetHeaderAddress(aux1))
                            [2 + nextcodes.word]);
                increment = 3;
                break;
            case BC_PUTFIELD:
                aux1 = Stack_Pop();
                aux2 = Stack_Pop();
                ((stack_slot_t *) Heap_GetHeaderAddress(aux2))
                        [2 + nextcodes.word] = aux1;
                increment = 3;
                break;
            case BC_INVOKEVIRTUAL:
            case BC_INVOKESPECIAL:
            case BC_INVOKESTATIC:
                if ((nextcodes.word & API_BIT_MASK_NATIVE_METHOD) == 0) {
                    // Store offset to current method bytecode
                    aux1 = (uint16_t) (pc - (mm_address_t) JavaClass_Data);
                    // Get pointer and method to call
                    method_ptr = JavaClass_GetMethod(nextcodes.word);
                    Mm_ReadNVM((mm_address_t) method_ptr,
                        sizeof(javaclass_method_header_t), (uint8_t *) &method);
                    // As arguments to this method has been added to stack,
                    // pointer is returned back to process this values in
                    // nex method call
                    Stack_Add(-method.arguments);

                    // Store current difference between stack pointer and
                    // local variables to restore when return
                    aux2 = Stack_CurrentPointer - localVariables;
                    // Local variables for next method
                    localVariables = Stack_CurrentPointer + 1;

                    // Get stack space for method to call and return info
                    Heap_GetBytes(sizeof(stack_slot_t) * (method.locals +
                        method.stack + method.arguments +
                            JVM_RETURN_INFO_STACK_SIZE));

                    // Add required space for local variables
                    Stack_Add(method.locals);
                    // Store offsets and current method index value
                    Stack_Push(aux1);
                    Stack_Push(index);
                    Stack_Push(aux2);

                    // Replace index by method index to call
                    index = nextcodes.word;
                    // Allocate program counter
                    pc = (mm_address_t) (JavaClass_Data + method.code);
                    increment = 0;
                } else {
                    if (BC_INVOKESTATIC != bytecode) {
                        // Get "this"
                        Stack_Pop();
                    }
                    Api_ExecuteNativeMethod(nextcodes.byte_l & API_ID_MASK);
                    increment = 3;
                }
                break;
            case BC_NEWARRAY:
                aux1 = Stack_Pop();
                Stack_Push(JvmArray_New(aux1, nextcodes.byte_l));
                increment = 2;
                break;
            default:
                EndlessLoop();
                break;
        }

        pc += increment;

    } while((bytecode != BC_IRETURN) && (bytecode != BC_RETURN));

    // Restore Heap pointer removing local variables
    Stack_Add(-method.locals);
    // Restore stack stored at the beginning
    Heap_SetBytes(sizeof(stack_slot_t) * (method.locals + method.stack +
            method.arguments));
}

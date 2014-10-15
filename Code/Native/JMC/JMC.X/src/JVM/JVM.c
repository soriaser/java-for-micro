#include "Common.h"

#include "JMC.h"
#include "JVM.h"
#include "Heap.h"
#include "Stack.h"

uint16_t *Jvm_LocalVariables;

void Jvm_Init(void)
{
    Heap_Init();
    Stack_Init();
}

void Jvm_ExecuteCode(uint16_t offset, uint16_t size)
{
    uint8_t bytecode = 0xFF;
    uint8_t pcIncrement = 0;

    for (uint16_t pc = 0; pc < size; pc += pcIncrement) {
        pcIncrement = 1;
        bytecode = Jmc_Code[offset + pc];

        switch (bytecode) {
            case BC_ALOAD_0:
            case BC_ALOAD_1:
            case BC_ALOAD_2:
            case BC_ALOAD_3:
                Stack_Push(Jvm_LocalVariables[bytecode - BC_ALOAD_0]);
                break;
        }
    }
}

void Jvm_ExecuteMethod(uint16_t jmcClassOffset, uint16_t jmcMethodId)
{
    uint16_t jmcMethodsOffset = Jmc_Classes[jmcClassOffset].methodsOffset;
    uint8_t jmcMethodsSize = Jmc_Classes[jmcClassOffset].methods;

    for (uint16_t ii = 0; ii < (jmcMethodsOffset + jmcMethodsSize); ii++) {
        if (jmcMethodId == Jmc_Methods[ii].id) {
            Jvm_LocalVariables = Stack_CurrentPointer + 1;
            Stack_CurrentPointer += Jmc_Methods[ii].locals;
            Stack_BasePointer = Stack_CurrentPointer;

            Jvm_ExecuteCode(Jmc_Methods[ii].offset, Jmc_Methods[ii].size);
            return;
        }
    }
}

#include "Common.h"
#include "JavaClass.h"
#include "MemoryManagement.h"

#define JAVACLASS_HEADER_VERSION 0x01

void JavaClass_Init(void)
{
    if (JAVACLASS_HEADER_VERSION != JavaClass_GetVersion()) {
        EndlessLoop();
    }
}

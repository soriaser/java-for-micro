#include "Common.h"
#include "JavaClass.h"
#include "MemoryManagement.h"

#define JAVACLASS_HEADER_VERSION (uint8_t) 0x01

uint16_t JavaClass_GetOnEventIndex(void)
{
    uint8_t flags = 0;
    uint8_t index = 0;
    javaclass_method_header_t *method;

    for (;index < JavaClass_GetNumberMethods(); index++) {
        method = JavaClass_GetMethod(index);
        flags = (Mm_GetU08((uint32_t) &((javaclass_method_header_t *)
                method)->flags));

        if (flags & JAVACLASS_METHOD_FLAG_ONEVENT) {
            return (Mm_GetU08((uint32_t) &((javaclass_method_header_t *)
                method)->id));
        }
    }

    return JAVACLASS_METHOD_ID_UNKNOWN;
}

void JavaClass_Init(void)
{
    uint8_t version = JavaClass_GetVersion();

    if (JAVACLASS_HEADER_VERSION != version) {
        EndlessLoop();
    }
}

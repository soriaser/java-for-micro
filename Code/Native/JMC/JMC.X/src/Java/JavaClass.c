#include "Common.h"
#include "JavaClass.h"

#define JAVACLASS_HEADER_VERSION 0x01

void JavaClass_Init(void)
{
    if (JAVACLASS_HEADER_VERSION !=
            ((javaclass_header_t *) JavaClass_Data)->version) {
        EndlessLoop();
    }
}

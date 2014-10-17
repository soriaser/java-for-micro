#include "Common.h"

#include "JVM.h"

#define JVM_HEADER_VERSION 0x01

void Jvm_PreInit(void)
{
    if (JVM_HEADER_VERSION != ((jvm_header_t *) Jvm_ClassData)->version) {
        Loop();
    }
}

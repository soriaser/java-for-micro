#include "Common.h"
#include "JMC.h"

NVMDATA uint8_t Jmc_Code[JMC_CODE_BUFFER_SIZE] = {
    #define STATIC_INIT_VALUE 0xFF
    #define STATIC_INIT_COUNT JMC_CODE_BUFFER_SIZE
    #include "InitializeArray.h"
    #undef STATIC_INIT_VALUE
    #undef STATIC_INIT_COUNT
};

NVMDATA jmc_f Jmc_Fields[JMC_FIELDS_BUFFER_SIZE] = {
    #define STATIC_INIT_VALUE {0xFF, 0xFFFF}
    #define STATIC_INIT_COUNT JMC_FIELDS_BUFFER_SIZE
    #include "InitializeArray.h"
    #undef STATIC_INIT_VALUE
    #undef STATIC_INIT_COUNT
};

NVMDATA jmc_m Jmc_Methods[JMC_METHODS_BUFFER_SIZE] = {
    #define STATIC_INIT_VALUE {0xFF, 0xFFFF, 0xFFFF, 0xFF}
    #define STATIC_INIT_COUNT JMC_METHODS_BUFFER_SIZE
    #include "InitializeArray.h"
    #undef STATIC_INIT_VALUE
    #undef STATIC_INIT_COUNT
};

NVMDATA jmc_c Jmc_Classes[JMC_CLASSES_BUFFER_SIZE] = {
    #define STATIC_INIT_VALUE {0xFFFF, 0xFF, 0xFFFF, 0xFF}
    #define STATIC_INIT_COUNT JMC_CLASSES_BUFFER_SIZE
    #include "InitializeArray.h"
    #undef STATIC_INIT_VALUE
    #undef STATIC_INIT_COUNT
};

NVMDATA uint16_t Jmc_CurrentOffsetCode = 0;

NVMDATA uint16_t Jmc_CurrentOffsetFields = 0;

NVMDATA uint16_t Jmc_CurrentOffsetMethods = 0;

NVMDATA uint16_t Jmc_CurrentOffsetClasses = 0;

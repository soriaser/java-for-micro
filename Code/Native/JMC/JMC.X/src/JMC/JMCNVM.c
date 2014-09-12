#include "Common.h"
#include "JMC.h"

NVMDATA uint8_t Jmc_Code[JMC_CODE_BUFFER_SIZE]; // TODO: Initialize to 0xFFs

NVMDATA jmc_f Jmc_Fields[JMC_FIELDS_BUFFER_SIZE]; // TODO: Initialize to 0xFFs

NVMDATA jmc_m Jmc_Methods[JMC_METHODS_BUFFER_SIZE]; // TODO: Initialize to 0xFFs

NVMDATA jmc_c Jmc_Classes[JMC_CLASSES_BUFFER_SIZE]; // TODO: Initialize to 0xFFs

NVMDATA uint16_t Jmc_CurrentOffsetCode = 0;

NVMDATA uint16_t Jmc_CurrentOffsetFields = 0;

NVMDATA uint16_t Jmc_CurrentOffsetMethods = 0;

NVMDATA uint16_t Jmc_CurrentOffsetClasses = 0;

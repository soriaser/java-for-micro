/* 
 * File:   Common.h
 * Author: Sudi
 *
 * Created on 12 de agosto de 2014, 17:13
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Features.h"
#include "Platform.h"

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed short long int24_t;
typedef unsigned short long uint24_t;
typedef signed long int32_t;
typedef unsigned long uint32_t;

typedef union {
  int16_t word;

  struct {
    int8_t byte_l;
    int8_t byte_h;
  };

} word_t;

#define NVMDATA //const

#ifndef NULL
#define NULL ((void *) 0)
#endif // NULL

#define EndlessLoop() do {} while (0x01)

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */


#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define COUNTOF(array) (sizeof(array)/sizeof(*array))
#define STATIC_ASSERT(...)

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;

typedef unsigned long ulong;

#endif // TYPES_H_INCLUDED

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <sys/param.h>
#include <stdbool.h>
#include <stdint.h>

#define COUNTOF(array) (sizeof(array)/sizeof(*array))
#define UNUSED(...)
#define STATIC_ASSERT(...)

#define BIT(i) (1 << (i))
#define GETBIT(a,i) (((a) >> (i)) & 1)
#define SETBIT(a,i) ((a) |= BIT(i))
#define CLRBIT(a,i) ((a) &= ~BIT(i))
#define ISSET(a,i) (((a) & BIT(i)) != 0)
#define ISCLR(a,i) (((a) & BIT(i)) == 0)

#endif // TYPES_H_INCLUDED

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <sys/param.h>
#include <stdbool.h>

typedef unsigned long ulong;

#define COUNTOF(array) (sizeof(array)/sizeof(*array))
#define STATIC_ASSERT(...)

#define SETBIT(a,i) ((a) |= 1<<(i))
#define CLRBIT(a,i) ((a) &= ~(1<<(i)))
#define ISSET(a,i) (((a) & (1<<(i))) != 0)
#define ISCLR(a,i) (((a) & (1<<(i))) == 0)

#endif // TYPES_H_INCLUDED

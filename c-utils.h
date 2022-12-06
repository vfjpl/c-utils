#ifndef C-UTILS_H_INCLUDED
#define C-UTILS_H_INCLUDED

#include <sys/time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//! stdlib
uint32_t util_atou(const char* str);
int util_div_upward(int x, int y);
void util_system(const char* format, ...);


//! string
void util_strcpy(char* dest, const char* src);
char* util_strcpy_p(char* dest, const char* src);
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);

const char* util_strafter(const char* str, const char* set);
void util_memcpy_swab(void* dest, const void* src, size_t size);


//! stdio
char* util_readfile(const char* name);


//! time
uint32_t util_time(void);
void util_gettimeofday(struct timeval* tv);
void util_settimeofday(uint32_t sec);


//! clock_monotonic
clock_t util_clock_monotonic(void);


#endif // C-UTILS_H_INCLUDED

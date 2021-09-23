#ifndef C-UTILS_H_INCLUDED
#define C-UTILS_H_INCLUDED

#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


//! stdlib
//atoi
uint32_t util_atou32(const char* str);


//! string
//strcpy
//stpcpy
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);


//! stdio
char* util_read_file(const char* name);
//fputs
void util_fputs(const char* str, FILE* stream);
//puts
void util_puts(const char* str);


//! time
uint32_t util_time_u32(void);
void util_gettimeofday_ptr(struct timeval* tv);
struct timeval util_gettimeofday_ret(void);
void util_settimeofday(uint32_t seconds);

clock_t util_clock_monotonic(void);
clock_t util_clock_monotonic_elapsed_ms(clock_t from);


#endif // C-UTILS_H_INCLUDED

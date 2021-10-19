#ifndef C-UTILS_H_INCLUDED
#define C-UTILS_H_INCLUDED

#include <sys/time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//! stdlib
uint32_t util_atou32(const char* str);
int util_div_ceil(int numerator, int denominator);


//! string
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);


//! stdio
char* util_read_file(const char* name);
void util_fputs(const char* str, FILE* stream);
void util_puts(const char* str);


//! time
uint32_t util_time_u32(void);
void util_gettimeofday_ptr(struct timeval* tv);
struct timeval util_gettimeofday_ret(void);
void util_settimeofday(uint32_t sec);


//! clock_monotonic
clock_t util_clock_monotonic(void);
clock_t util_clock_monotonic_future_sec(clock_t sec);
clock_t util_clock_monotonic_future_msec(clock_t msec);
clock_t util_clock_monotonic_elapsed_msec(clock_t from);


#endif // C-UTILS_H_INCLUDED

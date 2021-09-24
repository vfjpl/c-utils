#ifndef C-UTILS_H_INCLUDED
#define C-UTILS_H_INCLUDED

#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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


//! clock
clock_t util_seconds_to_clock_t(clock_t val);
clock_t util_clock_t_to_seconds(clock_t val);
clock_t util_milliseconds_to_clock_t(clock_t val);
clock_t util_clock_t_to_milliseconds(clock_t val);
clock_t util_clock_monotonic(void);


#endif // C-UTILS_H_INCLUDED

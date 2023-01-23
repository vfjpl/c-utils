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
int util_div_upward(int x, int y);
uint16_t util_load16(const void* ptr);
uint32_t util_load32(const void* ptr);
void util_store16(void* ptr, uint16_t val);
void util_store32(void* ptr, uint32_t val);
void util_system(const char* format, ...);


//! string
char* util_strcpy_p(char* dest, const char* src);
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);

const char* util_strafter(const char* str, const char* set);
void util_swab(const void* src, void* dest, ssize_t size);


//! stdio
char* util_readfile(const char* name);


//! time
uint32_t util_time(void);
void util_gettimeofday(struct timeval* tv);


#endif // C-UTILS_H_INCLUDED

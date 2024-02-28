#ifndef C-UTILS_H_INCLUDED
#define C-UTILS_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//! stdlib
uint16_t util_load16(const void* ptr);
uint32_t util_load32(const void* ptr);
void util_store16(void* ptr, uint16_t val);
void util_store32(void* ptr, uint32_t val);


//! string
void util_swab(const void* src, void* dest, ssize_t size);
void* util_mempcpy(void* dest, const void* src, size_t size);

char* util_strcpy_p(char* dest, const char* src);
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);


//! stdio
char* util_readfile(const char* name);


//! time
uint32_t util_time(void);
void util_gettimeofday(struct timeval* tv);
void util_settimeofday(const struct timeval* tv);


#endif // C-UTILS_H_INCLUDED

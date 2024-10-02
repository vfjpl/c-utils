#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdint.h>

uint16_t util_load16(const void* ptr);
uint32_t util_load32(const void* ptr);
void util_store16(void* ptr, uint16_t val);
void util_store32(void* ptr, uint32_t val);

float util_atof(const char* str);
uint32_t util_atou(const char* str);

char* util_strcpy_p(char* dest, const char* src);
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);

const char* util_strafter(const char* str, const char* delim);

void util_swab(const void* src, void* dest, ssize_t size);
void* util_mempcpy(void* dest, const void* src, size_t size);

const char* util_strerror(void);

int util_open(const char* filename, int flags);
void util_close(int* pfd);

char* util_asprintf(const char* format, ...);
char* util_readfile(const char* filename);

#endif // UTILS_H_INCLUDED

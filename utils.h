#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	char* buf;
	long size;
} string_t;

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

bool util_streq(const char* str1, const char* str2);
bool util_strneq(const char* str1, const char* str2, size_t size);
const char* util_strafter(const char* str, const char* delim);

void util_swab(const void* src, void* dest, ssize_t size);
void* util_mempcpy(void* dest, const void* src, size_t size);
void util_bzero(void* dest, size_t size);

const char* util_strerror(void);

void util_close(int* pfd);

string_t util_asprintf(const char* format, ...);
string_t util_readfile(const char* filename);

#endif // UTILS_H_INCLUDED

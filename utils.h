#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <sys/param.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	char* ptr;
	long size;
} string_t;

uint16_t util_load16(const void* ptr);
uint32_t util_load32(const void* ptr);
void util_store16(void* ptr, uint16_t val);
void util_store32(void* ptr, uint32_t val);

float util_atof(const char* str);
long util_atol(const char* str);
unsigned long util_atoul(const char* str);

char* util_strcpy_p(char* dest, const char* src);
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t n);
char* util_strcpy_np(char* dest, const char* src, size_t n);
size_t util_strcpy_nl(char* dest, const char* src, size_t n);

bool util_streq(const char* s1, const char* s2);
bool util_strneq(const char* s1, const char* s2, size_t n);
bool util_memeq(const void* p1, const void* p2, size_t n);

bool util_streq_until_any(const char* s1, const char* anyof, const char* s2);
const char* util_strafter_any(const char* str, const char* anyof);

void util_bzero(void* ptr, size_t n);
void util_swab(const void* src, void* dest, ssize_t n);
void* util_mempcpy(void* dest, const void* src, size_t n);

const char* util_strerror(void);
void util_close(int* pfd);
int util_isleap(int year);

string_t util_asprintf(const char* format, ...);
string_t util_readfile(const char* filename);

#endif // UTILS_H_INCLUDED

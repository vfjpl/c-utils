#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


typedef struct
{
	char* ptr;
	long size;
} string_t;


uint16_t util_load16(const void* ptr)
{
	uint16_t val;
	return *(uint16_t*)memcpy(&val, ptr, sizeof(val));
}
uint32_t util_load32(const void* ptr)
{
	uint32_t val;
	return *(uint32_t*)memcpy(&val, ptr, sizeof(val));
}
void util_store16(void* ptr, uint16_t val)
{
	memcpy(ptr, &val, sizeof(val));
}
void util_store32(void* ptr, uint32_t val)
{
	memcpy(ptr, &val, sizeof(val));
}
void util_copy16(void* dest, const void* src)
{
	memcpy(dest, src, sizeof(uint16_t));
}
void util_copy32(void* dest, const void* src)
{
	memcpy(dest, src, sizeof(uint32_t));
}


float util_atof(const char* str)
{
	return strtof(str, NULL);
}
uint32_t util_atou(const char* str)
{
	return strtoul(str, NULL, 0);
}


char* util_strcpy_p(char* dest, const char* src)
{
	return stpcpy(dest, src);
}
size_t util_strcpy_l(char* dest, const char* src)
{
	return util_strcpy_p(dest, src) - dest;
}
void util_strcpy_n(char* dest, const char* src, size_t n)
{
	--n;
	strncpy(dest, src, n)[n] = '\0';
}
char* util_strcpy_np(char* dest, const char* src, size_t n)
{
	--n;
	char* end = stpncpy(dest, src, n);
	dest[n] = '\0';
	return end;
}
size_t util_strcpy_nl(char* dest, const char* src, size_t n)
{
	return util_strcpy_np(dest, src, n) - dest;
}


void util_bzero(void* dest, size_t n)
{
	bzero(dest, n);
}
void util_swab(const void* src, void* dest, ssize_t n)
{
	swab(src, dest, n);
}
void* util_mempcpy(void* dest, const void* src, size_t n)
{
	return mempcpy(dest, src, n);
}
bool util_memeq(const void* ptr1, const void* ptr2, size_t n)
{
	return !bcmp(ptr1, ptr2, n);
}


bool util_streq(const char* str1, const char* str2)
{
	return !strcmp(str1, str2);
}
bool util_streq_n(const char* str1, const char* str2, size_t n)
{
	return !strncmp(str1, str2, n);
}
bool util_streq_until(const char* str1, const char* untilset, const char* str2)
{
	size_t len = strcspn(str1, untilset);
	if(strcspn(str2, untilset) == len)
		return util_memeq(str1, str2, len);
	else
		return false;
}
const char* util_strafter(const char* str, const char* afterset)
{
	str += strcspn(str, afterset);
	str += strspn(str, afterset);
	return str;
}


const char* util_strerror(void)
{
	return strerror(errno);
}


void util_close(int* pfd)
{
	int fd = *pfd;
	*pfd = -1;
	close(fd);
}


string_t util_asprintf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	string_t str = {0};
	str.size = vasprintf(&str.ptr, format, args);
	va_end(args);
	return str;
}
string_t util_readfile(const char* filename)
{
	string_t str = {0};
	FILE* file = fopen(filename, "re");
	if(file)
	{
		fseek(file, 0, SEEK_END);
		str.size = ftell(file);
		rewind(file);
		str.ptr = (char*)malloc(str.size + 1);
		fread(str.ptr, 1, str.size, file);
		str.ptr[str.size] = '\0';
		fclose(file);
	}
	return str;
}

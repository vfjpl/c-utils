#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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
void util_strcpy_n(char* dest, const char* src, size_t size)
{
	--size;
	strncpy(dest, src, size)[size] = '\0';
}
char* util_strcpy_np(char* dest, const char* src, size_t size)
{
	--size;
	char* end = stpncpy(dest, src, size);
	dest[size] = '\0';
	return end;
}
size_t util_strcpy_nl(char* dest, const char* src, size_t size)
{
	return util_strcpy_np(dest, src, size) - dest;
}

void util_swab(const void* src, void* dest, ssize_t size)
{
	swab(src, dest, size);
}
void* util_mempcpy(void* dest, const void* src, size_t size)
{
	return mempcpy(dest, src, size);    
}

void util_close(int* pfd)
{
	int fd = *pfd;
	*pfd = -1;
	close(fd);
}

char* util_asprintf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char* buffer = NULL;
	vasprintf(&buffer, format, args);
	va_end(args);
	return buffer;
}

char* util_readfile(const char* name)
{
	FILE* file = fopen(name, "r");
	if(!file) return NULL;
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	char* buffer = (char*)malloc(size + 1);
	fread(buffer, 1, size, file);
	buffer[size] = '\0';
	fclose(file);
	return buffer;
}

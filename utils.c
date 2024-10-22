#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>


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


bool util_streq(const char* str1, const char* str2)
{
	return !strcmp(str1, str2);
}
bool util_strneq(const char* str1, const char* str2, size_t size)
{
	return !strncmp(str1, str2, size);
}
const char* util_strafter(const char* str, const char* delim)
{
	str += strcspn(str, delim);
	str += strspn(str, delim);
	return str;
}


void util_swab(const void* src, void* dest, ssize_t size)
{
	swab(src, dest, size);
}
void* util_mempcpy(void* dest, const void* src, size_t size)
{
	return mempcpy(dest, src, size);
}


const char* util_strerror(void)
{
	return strerror(errno);
}


int util_open(const char* filename, int flags)
{
	int open_fd = open(filename, flags);
	if(open_fd < 0)
	{
		return -1;
	}
	if(fcntl(open_fd, F_SETFD, FD_CLOEXEC) < 0)
	{
		close(open_fd);
		return -1;
	}

	return open_fd;
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
char* util_readfile(const char* filename)
{
	FILE* file = fopen(filename, "r");
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

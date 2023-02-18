#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <sys/times.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


uint32_t util_atou32(const char* str)
{
	return strtoul(str, NULL, 0);
}
int util_div_upward(int x, int y)
{
	div_t result = div(x, y);
	return result.quot + (bool)result.rem;
}
uint16_t util_load16(const void* ptr)
{
	uint16_t val;
	memcpy(&val, ptr, sizeof(val));
	return val;
}
uint32_t util_load32(const void* ptr)
{
	uint32_t val;
	memcpy(&val, ptr, sizeof(val));
	return val;
}
void util_store16(void* ptr, uint16_t val)
{
	memcpy(ptr, &val, sizeof(val));
}
void util_store32(void* ptr, uint32_t val)
{
	memcpy(ptr, &val, sizeof(val));
}
void util_system(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	char* buffer;
	vasprintf(&buffer, format, args);
	system(buffer);
	free(buffer);
	va_end(args);
}


void util_swab(const void* src, void* dest, ssize_t size)
{
	swab(src, dest, size);
}
void* util_mempcpy(void* dest, const void* src, size_t size)
{
    return mempcpy(dest, src, size);
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
	strncpy(dest, src, size);
	dest[size] = '\0';
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

const char* util_strafter(const char* str, const char* set)
{
	str += strcspn(str, set);
	str += strspn(str, set);
	return str;
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


uint32_t util_time(void)
{
	return time(NULL);
}
void util_gettimeofday(struct timeval* tv)
{
	gettimeofday(tv, NULL);
}
void util_settimeofday(uint32_t sec)
{
	struct timeval tv = {sec};
	settimeofday(&tv, NULL);
}


static clock_t util_sec_to_clock_t(clock_t val)
{
	return val * sysconf(_SC_CLK_TCK);
}
static clock_t util_clock_t_to_sec(clock_t val)
{
	return val / sysconf(_SC_CLK_TCK);
}
static clock_t util_msec_to_clock_t(clock_t val)
{
	return util_sec_to_clock_t(val) / 1000;
}
static clock_t util_clock_t_to_msec(clock_t val)
{
	return util_clock_t_to_sec(val * 1000);
}

clock_t util_clock_monotonic(void)
{
	return times(NULL);
}

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

uint32_t util_atou32(const char* str)
{
	return strtoul(str, NULL, 0);
}

void util_strcpy_n(char* dest, const char* src, size_t size)
{
	--size;
	strncpy(dest, src, size);
	dest[size] = '\0';
}

char* util_strcpy_pn(char* dest, const char* src, size_t size)
{
	--size;
	char* ret = stpncpy(dest, src, size);
	dest[size] = '\0';
	return ret;
}

size_t util_strcpy_ln(char* dest, const char* src, size_t size)
{
	--size;
	char* end = stpncpy(dest, src, size);
	dest[size] = '\0';
	return end - dest;
}

size_t util_strcpy_l(char* dest, const char* src)
{
	return stpcpy(dest, str) - dest;
}

void util_fputs(const char* str, FILE* stream)
{
	fputs(str, stream);
	putc('\n', stream);
}

void util_puts(const char* str)
{
	fputs(str, stdout);
}

struct timeval util_gettimeofday(void)
{
	struct timeval ret;
	gettimeofday(&ret, NULL);
	return ret;
}

uint32_t util_time_u32(void)
{
	return time(NULL);
}

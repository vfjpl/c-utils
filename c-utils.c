#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <sys/times.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


uint32_t util_atou(const char* str)
{
	return strtoul(str, NULL, 0);
}
int util_div_upward(int numer, int denom)
{
	div_t result = div(numer, denom);
	return result.quot + (bool)result.rem;
}


void util_strcpy(char* dest, const char* src)
{
	strcpy(dest, src);
}
char* util_strcpy_p(char* dest, const char* src)
{
	return stpcpy(dest, src);
}
size_t util_strcpy_l(char* dest, const char* src)
{
	return stpcpy(dest, src) - dest;
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
void util_memcpy_swab(void* dest, const void* src, size_t size)
{
	swab(src, dest, size);
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

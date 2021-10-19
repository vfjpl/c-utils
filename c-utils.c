#include <sys/times.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


uint32_t util_atou32(const char* str)
{
	return strtoul(str, NULL, 0);
}
int util_div_ceil(int numerator, int denominator)
{
	div_t result = div(numerator, denominator);
	return result.quot + (bool)result.rem;
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


char* util_read_file(const char* name)
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
void util_fputs(const char* str, FILE* stream)
{
	fputs(str, stream);
	putc('\n', stream);
}
void util_puts(const char* str)
{
	fputs(str, stdout);
}


uint32_t util_time_u32(void)
{
	return time(NULL);
}
void util_gettimeofday_ptr(struct timeval* tv)
{
	gettimeofday(tv, NULL);
}
struct timeval util_gettimeofday_ret(void)
{
	struct timeval tv;
	util_gettimeofday_ptr(&tv);
	return tv;
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
clock_t util_clock_monotonic_future_sec(clock_t sec)
{
	return util_clock_monotonic() + util_sec_to_clock_t(sec);
}
clock_t util_clock_monotonic_future_msec(clock_t msec)
{
	return util_clock_monotonic() + util_msec_to_clock_t(msec);
}
clock_t util_clock_monotonic_elapsed_msec(clock_t from)
{
	return util_clock_t_to_msec(util_clock_monotonic() - from);
}

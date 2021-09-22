#include <sys/times.h>
#include <sys/time.h>
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
	--size;
	char* end = stpncpy(dest, src, size);
	dest[size] = '\0';
	return end - dest;
}


char* util_read_file(const char* name)
{
	FILE* file = fopen(name, "r");
	if(!file) return NULL;
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);
	char* buffer = (char*)malloc(size + 1);
	fread(buffer, sizeof(char), size, file);
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
	gettimeofday(&tv, NULL);
	return tv;
}
void util_settimeofday(uint32_t seconds)
{
	struct timeval tv = {seconds};
	settimeofday(&tv, NULL);
}


clock_t util_clock_monotonic(void)
{
	return times(NULL);
}
clock_t util_clock_monotonic_elapsed_ms(clock_t old)
{
	return ((times(NULL) - old) * 1000) / sysconf(_SC_CLK_TCK);
}

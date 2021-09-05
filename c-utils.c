#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

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

void util_fputs(const char* str, FILE* stream)
{
	fputs(str, stream);
	putc('\n', stream);
}

uint32_t util_atou32(const char* str)
{
	return strtoul(str, NULL, 0);
}

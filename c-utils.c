#include <string.h>
#include <stdio.h>

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
	return util_strcpy_pn(dest, src, size) - dest;
}

void util_fputs(const char* str, FILE* stream)
{
	fputs(str, stream);
	putc('\n', stream);
}

#include <string.h>
#include <stdio.h>

void util_strcpy(char* dest, const char* src, size_t size)
{
	size_t len = strnlen(src, size - 1);
	memcpy(dest, src, len);
	dest[len] = '\0';
}

void util_strncpy(char* dest, const char* src, size_t size)
{
	--size;
	strncpy(dest, src, size);
	dest[size] = '\0';
}

size_t util_strlcpy(char* dest, const char* src, size_t size)
{
	size_t ret = strlen(src);
	size_t len = (ret >= size) ? size - 1 : ret;
	memcpy(dest, src, len);
	dest[len] = '\0';
	return ret;
}

char* util_stpncpy(char* dest, const char* src, size_t size)
{
	--size;
	char* ret = stpncpy(dest, src, size);
	dest[size] = '\0';
	return ret;
}

void util_fputs(const char* str, FILE* stream)
{
	fputs(str, stream);
	putc('\n', stream);
}

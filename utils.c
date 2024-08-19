#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


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

void util_swab(const void* src, void* dest, ssize_t size)
{
	swab(src, dest, size);
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

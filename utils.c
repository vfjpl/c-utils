#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


typedef struct
{
	char* ptr;
	long size;
} string_t;


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
long util_atol(const char* str)
{
	return strtol(str, NULL, 0);
}
unsigned long util_atoul(const char* str)
{
	return strtoul(str, NULL, 0);
}


char* util_strcpy_p(char* dest, const char* src)
{
	return stpcpy(dest, src);//_GNU_SOURCE
}
size_t util_strcpy_l(char* dest, const char* src)
{
	return util_strcpy_p(dest, src) - dest;
}
void util_strcpy_n(char* dest, const char* src, size_t n)
{
	--n;
	strncpy(dest, src, n)[n] = '\0';
}
char* util_strcpy_np(char* dest, const char* src, size_t n)
{
	--n;
	char* end = stpncpy(dest, src, n);//_GNU_SOURCE
	dest[n] = '\0';
	return end;
}
size_t util_strcpy_nl(char* dest, const char* src, size_t n)
{
	return util_strcpy_np(dest, src, n) - dest;
}


bool util_streq(const char* s1, const char* s2)
{
	return !strcmp(s1, s2);
}
bool util_streq_n(const char* s1, const char* s2, size_t n)
{
	return !strncmp(s1, s2, n);
}
bool util_memeq(const void* p1, const void* p2, size_t n)
{
	return !bcmp(p1, p2, n);
}


bool util_streq_until_anyof(const char* s1, const char* anyof, const char* s2)
{
	size_t len = strcspn(s1, anyof);
	bool retval = (strcspn(s2, anyof) == len);
	if(retval)
		retval = util_memeq(s1, s2, len);
	return retval;
}
const char* util_str_after_anyof(const char* str, const char* anyof)
{
	str += strcspn(str, anyof);
	str += strspn(str, anyof);
	return str;
}


void util_bzero(void* ptr, size_t n)
{
	bzero(ptr, n);
}
void util_swab(const void* src, void* dest, ssize_t n)
{
	swab(src, dest, n);//_XOPEN_SOURCE
}
void* util_mempcpy(void* dest, const void* src, size_t n)
{
	return mempcpy(dest, src, n);//_GNU_SOURCE
}


const char* util_strerror(void)
{
	return strerror(errno);
}
void util_close(int* pfd)
{
	int fd = *pfd;
	*pfd = -1;
	close(fd);
}
int util_isleap(int year)
{
	return dysize(year) - 365;
}


string_t util_asprintf(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	string_t str = {0};
	str.size = vasprintf(&str.ptr, format, args);//_GNU_SOURCE
	va_end(args);
	return str;
}
string_t util_readfile(const char* path)
{
	string_t str = {0};
	FILE* file = fopen(path, "re");
	if(file != NULL)
	{
		fseek(file, 0, SEEK_END);
		str.size = ftell(file);
		rewind(file);
		str.ptr = (char*)malloc(str.size + 1);
		fread(str.ptr, 1, str.size, file);
		str.ptr[str.size] = '\0';
		fclose(file);
	}
	return str;
}
void util_copyfile(const char* src_path, const char* dest_path)
{
	FILE* src_file = fopen(src_path, "re");
	if(src_file != NULL)
	{
		FILE* dest_file = fopen(dest_path, "we");
		if(dest_file != NULL)
		{
			int ch;
			while((ch = getc(src_file)) != EOF)
				putc(ch, dest_file);

			fclose(dest_file);
		}
		fclose(src_file);
	}
}

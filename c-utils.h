#ifndef C-UTILS_H_INCLUDED
#define C-UTILS_H_INCLUDED

uint32_t util_atou32(const char* str);

size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);

char* util_read_file(const char* name);
void util_fputs(const char* str, FILE* stream);
void util_puts(const char* str);

uint32_t util_time_u32(void);
clock_t util_clock_monotonic(void);
struct timeval util_gettimeofday(void);

#endif // C-UTILS_H_INCLUDED

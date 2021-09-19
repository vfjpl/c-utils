#ifndef C-UTILS_H_INCLUDED
#define C-UTILS_H_INCLUDED


/// stdlib
//atoi
uint32_t util_atou32(const char* str);


/// string
//strcpy
//stpcpy
size_t util_strcpy_l(char* dest, const char* src);
void util_strcpy_n(char* dest, const char* src, size_t size);
char* util_strcpy_np(char* dest, const char* src, size_t size);
size_t util_strcpy_nl(char* dest, const char* src, size_t size);


/// stdio
char* util_read_file(const char* name);
//fputs
void util_fputs(const char* str, FILE* stream);
//puts
void util_puts(const char* str);


/// time
uint32_t util_time_u32(void);
struct timeval util_gettimeofday(void);
clock_t util_clock_monotonic(void);


#endif // C-UTILS_H_INCLUDED

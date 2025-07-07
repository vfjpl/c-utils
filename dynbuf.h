#ifndef DYNBUF_H_INCLUDED
#define DYNBUF_H_INCLUDED

#include <stdlib.h>
#include <string.h>

typedef struct
{
	void* ptr;
	long size;
} dynbuf_t;

dynbuf_t buf_append_impl(dynbuf_t dest, dynbuf_t src)
{
	dynbuf_t buf = {0};
	buf.size = dest.size + src.size;
	buf.ptr = realloc(dest.ptr, buf.size);
	memcpy(buf.ptr + dest.size, src.ptr, src.size);
	return buf;
}

#define buf_append_buf(dest, src)             dest = buf_append_impl(dest, src)
#define buf_append_ptr_size(dest, ptr, size)  buf_append_buf(dest, ((dynbuf_t){(void*)ptr, size}))
#define buf_append_ptr(dest, ptr)             buf_append_ptr_size(dest, ptr, sizeof(*ptr))
#define buf_append_type_val(dest, type, ...)  buf_append_ptr(dest, (&(type){__VA_ARGS__}))

#define buf_index(b, t, i)                   *((t*)b.ptr + i)
#define buf_elems(b, t)                      (b.size / sizeof(t))
#define buf_free(b)                          (free(b.ptr))


/*
EXAMPLE:

	int var1 = 69;
	int tab1[] = {2, 3, 4, 6, 8, 0};

	dynbuf_t buf1 = {0};
	buf_append_ptr(buf1, &var1);
	buf_append_type_val(buf1, int, 420);
	buf_append_ptr_size(buf1, tab1, sizeof(tab1));
	buf_append_type_val(buf1, int, 1337);
	buf_append_type_val(buf1, int[], 1, 3, 4, 6, 3, 4);
	for(long i = 0; i < buf_elems(buf1, int); ++i)
		printf("%d\n", buf_index(buf1, int, i));
	buf_free(buf1);


	struct_type var2;
	struct_type tab2[6];

	dynbuf_t buf2 = {0};
	buf_append_ptr(buf2, &var2);
	buf_append_type_val(buf2, struct_type);
	buf_append_ptr_size(buf2, tab2, sizeof(tab2));
	buf_append_type_val(buf2, struct_type, 2, 1, 3, 7);
	for(long i = 0; i < buf_elems(buf2, struct_type); ++i)
		process_struct(&buf_index(buf2, struct_type, i));
	buf_free(buf2);

*/

#endif // DYNBUF_H_INCLUDED

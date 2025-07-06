#ifndef DYNBUF_H_INCLUDED
#define DYNBUF_H_INCLUDED

#include <stdlib.h>
#include <string.h>


typedef struct
{
	void* buf;
	long size;
} dynbuf_t;

static dynbuf_t buf_append_impl(dynbuf_t dest, dynbuf_t src)
{
	dynbuf_t buf = {0};
	buf.size = dest.size + src.size;
	buf.ptr = realloc(dest.ptr, buf.size);
	memcpy(buf.ptr + dest.size, src.ptr, src.size);
	return buf;
}

#define buf_append(dest, src)                dest = buf_append_impl(dest, src)
#define buf_append_ptrsize(dest, ptr, size)  buf_append(dest, ((dynbuf_t){ptr, size}))
#define buf_append_byptr(dest, ptr)          buf_append_ptrsize(dest, ptr, sizeof(*ptr))
#define buf_append_typeval(dest, type, ...)  buf_append_byptr(dest, &((type){__VA_ARGS__}))

#define buf_index(b, t, i)                   *((t*)b.ptr + i)
#define buf_elems(b, t)                      (b.size / sizeof(t))
#define buf_free(b)                          (free(b.ptr))


/*
EXAMPLE:

	dynbuf_t buf1 = {0};
	int var1 = 2137;
	buf_append_byptr(buf1, &var1);
	buf_append_typeval(buf1, int, 1337);
	for(long i = 0; i < buf_elems(buf1, int); ++i)
		printf("%d\n", buf_index(buf1, int, i));
	buf_free(buf1);

	dynbuf_t buf2 = {0};
	struct_type var2 = {0};
	buf_append_byptr(buf2, &var2);
	buf_append_typeval(buf2, struct_type);
	buf_append_typeval(buf2, struct_type, 2, 1, 3, 7);
	buf_free(buf2);

*/

#endif // DYNBUF_H_INCLUDED

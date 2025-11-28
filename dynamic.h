#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include <stdlib.h>
#include <string.h>


typedef struct
{
	void* ptr;
	long size;
} buff_t;

static buff_t impl_buff_push(buff_t dest, buff_t src)
{
	dynbuf_t buf = {0};
	buf.size = dest.size + src.size;
	buf.ptr = realloc(dest.ptr, buf.size);
	memcpy(buf.ptr + dest.size, src.ptr, src.size);
	return buf;
}
#define impl_push_ptr_size(func, dest, ptr, size) func(dest, (buff_t){(void*)ptr, size})
#define impl_push_type_val(func, dest, type, val) func(dest, &(type){val}, sizeof(type))

#define buff_push(dest, src) dest = impl_buff_push(dest, src)
#define buff_push_ptr_size(dest, ptr, size) impl_push_ptr_size(buff_push, dest, ptr, size)
#define buff_push_type_val(dest, type, val) impl_push_type_val(buff_push, dest, ptr, size)


typedef struct
{
	long write;
	long read;
	buff_t buff;
} queue_t;

static void queue_push(queue_t* dest, buff_t src)
{
	const long write_old = dest->write;
	if(write_old != dest->read)
	{
		const long write_new = write_old + src.size;
		dest->write = (write_new != dest->buff.size) ? write_new : 0;
		memcpy(dest->buff.ptr + write_old, src.ptr, src.size);
	}
	else
	{
		buff_push(dest->buff, src);
	}
}
#define queue_push_ptr_size(dest, ptr, size) impl_push_ptr_size(queue_push, &dest, ptr, size)
#define queue_push_type_val(dest, type, val) impl_push_type_val(queue_push, &dest, type, val)


#endif // DYNAMIC_H_INCLUDED

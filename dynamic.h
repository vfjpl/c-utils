#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include <stdlib.h>
#include <string.h>


typedef struct
{
	void* ptr;
	long size;
} buff_t;

static buff_t impl_buff_push_buff_impl(buff_t dest, buff_t src)
{
	buff_t buff = {0};
	buff.size = dest.size + src.size;
	buff.ptr = realloc(dest.ptr, buff.size);
	memcpy(buff.ptr + dest.size, src.ptr, src.size);
	return buff;
}
#define impl_ptr_size_impl(push_func, dest, ptr, size) push_func(dest, ((buff_t){(void*)ptr, size}))
#define impl_type_val_impl(push_func, dest, type, val) push_func(dest, &(type){val}, sizeof(type))

#define buff_push_buff(dest, src) dest = impl_buff_push_buff_impl(dest, src)
#define buff_push_ptr_size(dest, ptr, size) impl_ptr_size_impl(buff_push_buff, dest, ptr, size)
#define buff_push_type_val(dest, type, val) impl_type_val_impl(buff_push_ptr_size, dest, type, val)


typedef struct
{
	long write;
	long read;
	buff_t buff;
} queue_t;

static void queue_push_buff(queue_t* dest, buff_t src)
{
	const long old_write = dest->write;
	if(old_write != dest->read)
	{
		const long new_write = old_write + src.size;
		dest->write = (new_write != dest->buff.size) ? new_write : 0;
		memcpy(dest->buff.ptr + old_write, src.ptr, src.size);
	}
	else
	{
		buff_push_buff(dest->buff, src);
	}
}
#define queue_push_ptr_size(dest, ptr, size) impl_ptr_size_impl(queue_push_buff, dest, ptr, size)
#define queue_push_type_val(dest, type, val) impl_type_val_impl(queue_push_ptr_size, dest, type, val)


#endif // DYNAMIC_H_INCLUDED

#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include <stdbool.h>
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
#define impl_ptr_size_impl(func, dest, ptr, size) func(dest, ((buff_t){(void*)ptr, size}))
#define impl_type_val_impl(func, dest, type, val) func(dest, &(type){val}, sizeof(type))


#define buff_push_buff(dest, src) dest = impl_buff_push_buff_impl(dest, src)
#define buff_push_ptr_size(dest, ptr, size) impl_ptr_size_impl(buff_push_buff, dest, ptr, size)
#define buff_push_type_val(dest, type, val) impl_type_val_impl(buff_push_ptr_size, dest, type, val)



typedef struct
{
	buff_t buff;
	long read;
	long write;
} queue_t;


static void queue_push_buff(queue_t* dest, buff_t src)
{
	const long old_write = dest->write;
	const long new_write = old_write + src.size;
	const bool is_not_end = (new_write < dest->buff.size);
	const long new_write_on_push = is_not_end ? old_write : new_write;
	const long new_write_wrapped = is_not_end ? new_write : 0;
	if(new_write_wrapped != dest->read)//is_not_full
	{
		dest->write = new_write_wrapped;
		memcpy(dest->buff.ptr + old_write, src.ptr, src.size);
	}
	else
	{
		dest->write = new_write_on_push;
		buff_push_buff(dest->buff, src);
	}
}
#define queue_push_ptr_size(dest, ptr, size) impl_ptr_size_impl(queue_push_buff, dest, ptr, size)
#define queue_push_type_val(dest, type, val) impl_type_val_impl(queue_push_ptr_size, dest, type, val)

#define queue_is_empty(dest) (dest->read == dest->write)
#define queue_front_type(dest, type) *(type*)(dest->buff.ptr + dest->read)

static void queue_pop_buff(queue_t* src, buff_t dest)
{
	const long old_read = src->read;
	const long new_read = old_read + dest.size;
	src->read = (new_read < src->buff.size) ? new_read : 0;
	memcpy(dest.ptr, src->buff.ptr + old_read, dest.size);
}


#endif // DYNAMIC_H_INCLUDED

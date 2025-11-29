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
#define template_ptr_size_buff(func, container, ptr, size) func(container, ((buff_t){(void*)ptr, size}))
#define template_ptr_buff(func, container, ptr) template_ptr_size_buff(func, container, ptr, sizeof(*ptr))
#define template_var_buff(func, container, var) template_ptr_size_buff(func, container, &var, sizeof(var))
#define template_type_val_buff(func, container, type, val) template_ptr_size_buff(func, container, &(type){val}, sizeof(type))


///start interface
#define buff_push_buff(dest, src) dest = impl_buff_push_buff_impl(dest, src)
#define buff_push_ptr_size(dest, ptr, size) template_ptr_size_buff(buff_push_buff, dest, ptr, size)
#define buff_push_ptr(dest, ptr) template_ptr_buff(buff_push_buff, dest, ptr)
#define buff_push_var(dest, var) template_var_buff(buff_push_buff, dest, var)
#define buff_push_type_val(dest, type, val) template_type_val_buff(buff_push_buff, dest, type, val)
///end interface



typedef struct
{
	buff_t buff;
	long read;
	long write;
} queue_t;


///start interface
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
#define queue_push_ptr_size(dest, ptr, size) template_ptr_size_buff(queue_push_buff, dest, ptr, size)
#define queue_push_ptr(dest, ptr) template_ptr_buff(queue_push_buff, dest, ptr)
#define queue_push_var(dest, var) template_var_buff(queue_push_buff, dest, var)
#define queue_push_type_val(dest, type, val) template_type_val_buff(queue_push_buff, dest, type, val)

static void queue_pop_buff(queue_t* src, buff_t dest)
{
	const long old_read = src->read;
	const long new_read = old_read + dest.size;
	src->read = (new_read < src->buff.size) ? new_read : 0;
	memcpy(dest.ptr, src->buff.ptr + old_read, dest.size);
}
#define queue_pop_ptr_size(src, ptr, size) template_ptr_size_buff(queue_pop_buff, src, ptr, size)
#define queue_pop_ptr(src, ptr) template_ptr_buff(queue_pop_buff, src, ptr)
#define queue_pop_var(src, var) template_var_buff(queue_pop_buff, src, var)
///end interface


#endif // DYNAMIC_H_INCLUDED

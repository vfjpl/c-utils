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


#define template_ptr_size_buff(func, obj, ptr, size)  func(obj, ((buff_t){(void*)ptr, size}))
#define template_ptr_buff(func, obj, ptr)             template_ptr_size_buff(func, obj, ptr, sizeof(*ptr))
#define template_var_buff(func, obj, var)             template_ptr_size_buff(func, obj, &var, sizeof(var))
#define template_type_val_buff(func, obj, type, val)  template_ptr_size_buff(func, obj, &(type){val}, sizeof(type))


static buff_t impl_buff_push_buff_impl(buff_t dest, buff_t src)
{
	buff_t buff = {0};
	buff.size = dest.size + src.size;
	buff.ptr = realloc(dest.ptr, buff.size);
	memcpy(buff.ptr + dest.size, src.ptr, src.size);
	return buff;
}
static buff_t impl_buff_free_impl(buff_t buff)
{
	free(buff.ptr);
	return (buff_t){0};
}


///begin user interface
#define buff_push_buff(dest, src)            dest = impl_buff_push_buff_impl(dest, src)
#define buff_push_ptr_size(dest, ptr, size)  template_ptr_size_buff(buff_push_buff, dest, ptr, size)
#define buff_push_ptr(dest, ptr)             template_ptr_buff(buff_push_buff, dest, ptr)
#define buff_push_var(dest, var)             template_var_buff(buff_push_buff, dest, var)
#define buff_push_type_val(dest, type, val)  template_type_val_buff(buff_push_buff, dest, type, val)

#define buff_free(buff)                      buff = impl_buff_free_impl(buff)
///end user interface




typedef struct
{
	buff_t buff;
	long head;
	long tail;
} queue_t;


static void impl_queue_push_buff_impl(queue_t* dest, buff_t src)
{
	const long old_tail = dest->tail;
	const long new_index = old_tail + src.size;
	const long new_index_wrapped = (new_index < dest->buff.size) ? new_index : 0;
	if(new_index_wrapped != dest->head)
	{
		memcpy(dest->buff.ptr + old_tail, src.ptr, src.size);
		dest->tail = new_index_wrapped;
	}
	else
	{
		buff_push_buff(dest->buff, src);
		dest->head = new_index;
	}
}
static bool impl_queue_pop_buff_impl(queue_t* src, buff_t dest)
{
	const long old_head = src->head;
	const bool retval = (old_head != src->tail);
	if(retval)
	{
		const long new_index = old_head + dest.size;
		const long new_index_wrapped = (new_index < src->buff.size) ? new_index : 0;
		memcpy(dest.ptr, src->buff.ptr + old_head, dest.size);
		src->head = new_index_wrapped;
	}
	return retval;
}


///begin user interface
#define queue_push_buff(dest, src)            impl_queue_push_buff_impl(&dest, src)
#define queue_push_ptr_size(dest, ptr, size)  template_ptr_size_buff(queue_push_buff, dest, ptr, size)
#define queue_push_ptr(dest, ptr)             template_ptr_buff(queue_push_buff, dest, ptr)
#define queue_push_var(dest, var)             template_var_buff(queue_push_buff, dest, var)
#define queue_push_type_val(dest, type, val)  template_type_val_buff(queue_push_buff, dest, type, val)

#define queue_pop_buff(src, dest)             impl_queue_pop_buff_impl(&src, dest)
#define queue_pop_ptr_size(src, ptr, size)    template_ptr_size_buff(queue_pop_buff, src, ptr, size)
#define queue_pop_ptr(src, ptr)               template_ptr_buff(queue_pop_buff, src, ptr)
#define queue_pop_var(src, var)               template_var_buff(queue_pop_buff, src, var)
///end user interface


#endif // DYNAMIC_H_INCLUDED

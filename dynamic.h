#ifndef DYNAMIC_H_INCLUDED
#define DYNAMIC_H_INCLUDED

#include <stdlib.h>
#include <string.h>


typedef struct
{
	void* ptr;
	long size;
} buff_t;


#define template_ptr_size_buff(func, container, ptr, size)  func(container, ((buff_t){(void*)ptr, size}))
#define template_ptr_buff(func, container, ptr)             template_ptr_size_buff(func, container, ptr, sizeof(*ptr))
#define template_var_buff(func, container, var)             template_ptr_size_buff(func, container, &var, sizeof(var))
#define template_type_val_buff(func, container, type, val)  template_ptr_size_buff(func, container, &(type){val}, sizeof(type))


static buff_t impl_buff_push_buff_impl(buff_t dest, buff_t src)
{
	buff_t buff = {0};
	buff.size = dest.size + src.size;
	buff.ptr = realloc(dest.ptr, buff.size);
	memcpy(buff.ptr + dest.size, src.ptr, src.size);
	return buff;
}


///start user interface
#define buff_push_buff(dest, src)            dest = impl_buff_push_buff_impl(dest, src)
#define buff_push_ptr_size(dest, ptr, size)  template_ptr_size_buff(buff_push_buff, dest, ptr, size)
#define buff_push_ptr(dest, ptr)             template_ptr_buff(buff_push_buff, dest, ptr)
#define buff_push_var(dest, var)             template_var_buff(buff_push_buff, dest, var)
#define buff_push_type_val(dest, type, val)  template_type_val_buff(buff_push_buff, dest, type, val)
///end user interface




typedef struct
{
	buff_t buff;
	long head;
	long tail;
} queue_t;


///start user interface
static void queue_push_buff(queue_t* dest, buff_t src)
{
	const long old_tail = dest->tail;
	const long new_tail = old_tail + src.size;
	const long new_tail_wrapped = (new_tail < dest->buff.size) ? new_tail : 0;
	if(new_tail_wrapped != dest->head)
	{
		dest->tail = new_tail_wrapped;
		memcpy(dest->buff.ptr + old_tail, src.ptr, src.size);
	}
	else
	{
		//bug: fix head
		buff_push_buff(dest->buff, src);
	}
}
#define queue_push_ptr_size(dest, ptr, size)  template_ptr_size_buff(queue_push_buff, dest, ptr, size)
#define queue_push_ptr(dest, ptr)             template_ptr_buff(queue_push_buff, dest, ptr)
#define queue_push_var(dest, var)             template_var_buff(queue_push_buff, dest, var)
#define queue_push_type_val(dest, type, val)  template_type_val_buff(queue_push_buff, dest, type, val)


static void queue_pop_buff(queue_t* src, buff_t dest)
{
	const long old_head = src->head;
	const long new_head = old_head + dest.size;
	src->head = (new_head < src->buff.size) ? new_head : 0;
	memcpy(dest.ptr, src->buff.ptr + old_head, dest.size);
}
#define queue_pop_ptr_size(src, ptr, size)  template_ptr_size_buff(queue_pop_buff, src, ptr, size)
#define queue_pop_ptr(src, ptr)             template_ptr_buff(queue_pop_buff, src, ptr)
#define queue_pop_var(src, var)             template_var_buff(queue_pop_buff, src, var)


#define queue_front_type(queue, type)  *(type*)(queue->buff.ptr + queue->head)


#define queue_is_empty(queue)  (queue->head == queue->tail)
///end user interface


#endif // DYNAMIC_H_INCLUDED

#pragma once
#include "common.h"

typedef void (*push_func)(base_s * base, base_s * against,void * head, ssize_t n);

typedef gboolean (*pop_func)(base_s * base, void ** phead, int *n);

typedef void (*clear_func)(base_s * base, void * ptr);

typedef struct base_s{
	int fd;
	GList * buf;
	push_func  push;
	pop_func *pop;
	clear_func clear;
}base_s;

inline void base_init(base_s * base, push_func push,clear_func clear,pop_func pop){
	base->push = push;
	base->pop = pop;
	base->clear = clear;
	
}

gboolean base_get_data(base_s * base, void ** phead);

inline int base_get_fd(base_s * base){
	return base->fd;
}


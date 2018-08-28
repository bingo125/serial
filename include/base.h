#pragma once

#include "common.h"
#include "base.h"

typedef void (*push_func)(void * base,void * head, ssize_t n);

typedef gboolean (*pop_func)(void * base, void ** phead, int *n);

typedef void (*clear_func)(void * base, void * ptr);

typedef struct base_s{
	int fd;
	GList * buf;
	push_func  push;
	pop_func pop;
	clear_func clear;
}base_s;


void base_init(base_s * base, int fd,push_func push,pop_func pop,clear_func clear);
 
gboolean base_get_data(base_s * base, void ** phead);

int base_get_fd(base_s * base);

void base_clear(base_s * base, void * ptr);

void base_deinit(base_s * base);

void base_push(base_s * base,void * data);



#include "base.h"

// void base_push(base_s * base,void * head, ssize_t n){
	// char * pmem = g_new (char , n);
	// memcpy(pmem, head, n);
	// base->buf = g_list_append(base->buf, pmem);
// }

gboolean base_get_data(base_s * base, void ** phead){
	*phead = NULL;
	if(base->buf){
		*phead = base->buf->data;
		base->buf = g_list_delete_link (base->buf,base->buf);
		return TRUE;
	}
	return FALSE;
}

void base_clear(base_s * base, void * ptr){
	if(base->clear){
		return base->clear(base,ptr);
	}
	g_free(ptr);
}

void each_callback(gpointer data, gpointer user_data)
{
	base_s * base = user_data;
	base_clear(base, data);
}


void base_deinit(base_s * base){
	g_list_foreach (base->buf, each_callback,  base);
	g_list_free  (base->buf);
}

inline int base_get_fd(base_s * base){
	return base->fd;
}

inline void base_push(base_s * base,void * data){
	base->buf = g_list_append(base->buf, data);
}

void base_init(base_s * base, int fd,push_func push,pop_func pop,clear_func clear){
	base->fd = fd;
	base->push = push;
	base->pop = pop;
	base->clear = clear;
}



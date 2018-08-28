#include "base.h"

void base_push(base_s * base,void * head, ssize_t n){
	char * pmem = g_new (char , n);
	memcpy(pmem, head, n);
	base->buf = g_list_append(base->buf, pmem);
}

gboolean base_get_data(base_s * base, void ** phead){
	*phead = NULL;
	if(base->buf){
		*phead = base->buf->data;
		base->buf = g_list_delete_link (base->buf,base->buf);
		return TRUE;
	}
	return FALSE;
}

void base_func(base_s * base, void * ptr){
	if(base->clear){
		return base->clear(base,ptr);
	}
	g_free(ptr);
	return true;
}


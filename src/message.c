#include "message.h"
#include "common.h"

#define USER_DATA_BIT ()

void message_clear(message_s *msg){
	g_free(msg->buf);
	g_free(msg);
	return true;
}

gboolean message_is_valid(message_s *){
	
}

void message_set_data(message_s *msg, guchar * ptr, guint8 sz){
	msg->buf = realloc(msg->buf, sz +msg->sz);
	memcpy(msg->buf[x],ptr, sz)
}



arr_t arr_check(guchar * parr,gint sz， gint** result){
	arr_t ret = arr_fail;
	int i = 0;
	if(sz < 6)
		return arr_contiue;

	if(parr[0] != 0x55){
		*result  = 1;
		goto out;
	}
	
	if(parr[1] != 0xaa){
		*result  = 2;
		goto out;
	}
	int len = parr[3];
	
	if(len +x < sz){
		return arr_contiue;
	}
	*result = len;
	if(check_sum(parr, len)){
		goto out;
	}
	return arr_ok;
out:
	return arr_contiue;
}

guchar  check_sum(guchar *pattr , int sz) {
    int i;
    u_char sum = 0;
    for(i = 0; i < sz ; i++) {
        sum ^= pattr[i];
    }
    return sum;
}





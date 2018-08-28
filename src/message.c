#include "common.h"
#include "message.h"
#include "translate.h"

guchar  check_sum(guchar *pattr , int sz) ;

void message_clear(message_s *msg){
	g_free(msg->buf);
	g_free(msg);
}

gboolean message_is_valid(message_s *msg){
  if(msg->sz <MESSAGE_MIN){
    return FALSE;
  }
  if(!(msg->buf[0] == 0xaa &&msg->buf[1] == 0x55)){
    return FALSE;
  }
  int sz = msg->buf[2];

  if(check_sum(msg->buf, sz)){
    return FALSE;
  }
  return TRUE;
}

void message_set_data(message_s *msg, guchar * ptr, guint8 sz){
  msg->buf = realloc(msg->buf, sz + msg->sz);
  if(!msg->buf){
    memcpy(msg->buf+USER_DATA_BIT,ptr, sz);
  }
}

//arr_t arr_check(guchar * parr,gint sz, gint** result){
//  arr_t ret = arr_fail;
//  int i = 0;
//  if(sz < MESSAGE_MIN)
//    return arr_contiue;
//
//  if(parr[0] != 0x55){
//    *result  = 1;
//    goto out;
//  }
//
//  if(parr[1] != 0xaa){
//    *result  = 2;
//    goto out;
//  }
//  int len = parr[USER_LEN_BIT];
//
//  if(len +x < sz){
//    return arr_contiue;
//  }
//  *result = len;
//  if(check_sum(parr, len)){
//    goto out;
//  }
//  return arr_ok;
//out:
//  return arr_contiue;
//}

guchar  check_sum(guchar *pattr , int sz) {
  int i;
  u_char sum = 0;
  for(i = 0; i < sz ; i++) {
    sum ^= pattr[i];
  }
  return sum;
}

gboolean arr_cmp(guchar * gonna_arrs,int i ){
  arr2str_s *ori_arr =&arr2str[i];
  for(int i = 0; i < ori_arr->len; i ++){
    if(i == 3||i == 4){
      continue;
    }
    if(gonna_arrs[ i] != ori_arr->arrs[i]){
      goto no_match;
    }
  }
  return TRUE;
no_match:
  return FALSE;
}

void arr_show(guchar * arr, guint sz){
  printf("<---------");
  for (int i = 0; i < sz; i ++){
    printf("0x%02x  ", arr[i]);
  }
  printf("--------->\n");
}

static guchar s_seq = 0;

void message_update(message_s *msg){
	msg->buf[USER_SEQ_BIT] = s_seq++;
	int len = msg->buf[USER_LEN_BIT];
	msg->buf[len -1]= check_sum (msg->buf, len-1);
}

message_s*  message_new_by_socket(guchar * buf, guint8 sz){
	message_s *msg = g_new (message_s, 1);
	msg->buf =g_new(guchar, sz);
	memcpy(&msg->buf, buf, sz);
	msg->sz = sz;
	return msg;
}



gboolean message_is_ack(message_s *msg){
	if(msg->buf[USER_LEN_BIT] == 6){
		return true;
	}
	return false;
}

guchar message_get_seq(message_s *msg){
	return msg->buf[USER_SEQ_BIT];
}

guchar message_lenth(message_s *msg){
	return msg->buf[USER_LEN_BIT];
}


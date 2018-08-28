#pragma once
#include "common.h"
typedef struct message_s{
	guchar *buf;
	guint8 sz;
}message_s;

typedef enum arr_t{
	arr_fail,
	arr_ok,
	arr_contiue,
}arr_t;

static u_char write_seq = 0;

arr_t arr_check(guchar * parr, guchar** pend ,int sz);


gboolean message_is_valid(message_s *);

gboolean message_is_ack(message_s *);

guchar message_get_seq(message_s *);

message_s* message_cover_ack(message_s *);

void message_set_data(message_s *,guchar * ptr, guint8 sz);

gboolean message_new_by_recive(guchar * buf, guint8 sz);

gboolean message_new_by_socket(guchar * buf, guint8 sz);

void message_set_data(message_s *msg, guchar * ptr, guint8 sz);

inline guint8 message_lenth(message_s *msg){
	return msg->sz;
}



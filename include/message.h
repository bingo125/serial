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

#define USER_DATA_BIT (6)
#define USER_LEN_BIT (2)
#define USER_SEQ_BIT (3)
#define MESSAGE_ACK_LEN (6)
#define MESSAGE_MIN (6)

arr_t arr_check(guchar * parr,gint sz, gint** result);

gboolean message_is_valid(message_s *);

gboolean message_is_ack(message_s *);

guchar message_get_seq(message_s *);

message_s* message_cover_ack(message_s *);

void message_set_data(message_s *,guchar * ptr, guint8 sz);

gboolean message_new_by_recive(guchar * buf, guint8 sz);

message_s*  message_new_by_socket(guchar * buf, guint8 sz);

void message_update(message_s *);

void message_set_data(message_s *msg, guchar * ptr, guint8 sz);

gboolean arr_cmp(guchar * gonna_arrs,int i );

void arr_show(guchar * arr, guint sz);

guchar  check_sum(guchar *pattr , int sz);
void message_clear(message_s *msg);

guchar message_lenth(message_s *msg);




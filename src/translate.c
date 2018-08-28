#include "translate.h"
static  translate_s *  translate = NULL;

#define ADDSTR(name)  (name##_str)

#define describe(name, func) {\
		.arrs = name,\
		.str = ADDSTR(name),\
		.len = ARRSIZE(name),\
		.fn = func,\
		}
	
char * arr2str_2byte(char * ptr, guchar * parr, ssize_t sz){
	char * tmp = NULL;
	guint16 num = 0;
	num = parr[0]<<8| parr[1];
	if(asprintf(&tmp, "%s=%u", ptr, num) <0){
		perror("failure malloc ");
	}
	return tmp;
}

char * arr2str_4byte(char * ptr, guchar * parr, ssize_t sz){
	char * tmp = NULL;
	guint16 strat, end ;
	strat = parr[0]<<8| parr[1];
	end = parr[2]<<8| parr[3];
	if(asprintf(&tmp, "%s=%u,%u", ptr, strat, end) <0){
		perror("failure malloc ");
	}
	return tmp;
}

arr2str_s arr2str[] =
{
	describe(mcu_cmd_mute,NULL),
	describe(mcu_cmd_play_toggle,NULL),
	describe(mcu_cmd_next,NULL),
	describe(mcu_cmd_pre,NULL),
	describe(mcu_cmd_forward_seek,NULL),
	describe(mcu_cmd_back_seek,NULL),
	describe(mcu_cmd_play,NULL),
	describe(mcu_cmd_pause,NULL),
	describe(mcu_cmd_back_dir,NULL),
	describe(mcu_cmd_single_loop,NULL),
	describe(mcu_cmd_list_loop,NULL),
	describe(mcu_cmd_dir_loop,NULL),
	describe(mcu_cmd_play_spec,arr2str_2byte),
	describe(mcu_cmd_dir_next,arr2str_2byte),
	describe(mcu_info_play_pause,NULL),
	describe(mcu_info_loop,NULL),
	describe(mcu_info_play_time,NULL),
	describe(mcu_info_play_total_time,NULL),
	describe(mcu_info_index,NULL),
	describe(mcu_info_total,NULL),
	describe(mcu_info_name,NULL),
	describe(mcu_info_singer,NULL),
	describe(mcu_info_ablume,NULL),
	describe(mcu_info_file_name,arr2str_4byte),
};

gboolean feedback_play_pause(guchar *parr, int *sz, gchar * str);
gboolean feedback_loop(guchar *parr, int *sz, gchar * str);
gboolean feedback_time_play(guchar *parr, int *sz, gchar * str);
gboolean feedback_time_song(guchar *parr, int *sz, gchar * str);
gboolean feedback_cur_dirname(guchar *parr, int *sz, gchar * str);
gboolean feedback_total_song(guchar *parr, int *sz, gchar * str);

gboolean feedback_file_names(guchar *parr, int *sz, gchar * str);
gboolean feedback_singer(guchar *parr, int *sz, gchar * str);
gboolean feedback_ablum(guchar *parr, int *sz, gchar * str);
gboolean feedback_name(guchar *parr, int *sz, gchar * str);





str2arr_s str2arr[] =
{
	describe(arm_feedback_play_pause,feedback_play_pause),
	describe(arm_feedback_loop,feedback_loop),
	describe(arm_feedback_time_play,feedback_time_play),
	describe(arm_feedback_time_song,feedback_time_song),
	describe(arm_feedback_cur,feedback_cur_dirname),
	describe(arm_feedback_total_song,feedback_total_song),
	describe(arm_feedback_file_names,feedback_file_names),
	describe(arm_feedback_singer,feedback_singer),
	describe(arm_feedback_ablum,feedback_ablum),
	describe(arm_feedback_name,feedback_name),
	describe(arm_send_player_status,NULL),
};
void translate_deinit(){
   // do nothing
}

translate_s *translate_get(){
	return translate;
}


translate_s *translate_init(base_s * socket, base_s * serial){
	if(!translate){
		translate_s * ts= g_new0 (translate_s, 1);
		ts->serial = serial;
		ts->socket = socket;
	}
	return translate;
}
#define BUFSZ 128


void translate_arr(translate_s *ts, guchar * arrs, guint sz){
	gint arr_sz = ARRSIZE (arr2str);
	for(int i = 0; i < arr_sz; i ++){
		if(arr_cmp (arrs, i)){
			arr2str_s *parr = &arr2str[i];
			if(parr->fn){
				guchar sz = parr->arrs[USER_LEN_BIT] - 7;
				char * pch = parr->fn(parr->str,(void*) &parr->arrs[USER_DATA_BIT], sz);
				base_push (ts->socket, pch);
			}
			return;
		}
	}
}

void translate_string(translate_s *ts, char * str){
	gint arr_sz = ARRSIZE (str2arr);
	for(int i  = 0; i < arr_sz; i ++){
		gchar * arr_str = str2arr[i].str;
		int len = strlen(arr_str);
		analytic_parameter_str fn = str2arr[i].fn;
		if(strncmp(str,arr_str, len)){
			message_s*  msg = message_new_by_socket ((guchar *)str2arr[i].arrs, str2arr[i].len);
			if(fn){
				//skip '='
				guchar usrdata [BUFSZ];
				gint sz;
				fn(usrdata, &sz,++str);
				if(sz){
					message_set_data (msg, usrdata, sz);
				}
			}
			message_update(msg);
			base_push (ts->serial, msg);
			return;
		}
	}
	
}

gboolean feedback_play_pause(guchar *parr, int *sz, gchar * str){
	*sz = 1;
	if(strcmp(str,"play")){
		parr[0] = 0x01;
		return TRUE;
	}else if(strcmp(str,"pause")){
		parr[0] = 0x02;
		return TRUE;
	}
	parr[0] = 0x00;
	return FALSE;
}

gboolean feedback_loop(guchar *parr, int *sz, gchar * str){
	//todo 
	return FALSE;
}

gboolean feedback_time_play(guchar *parr, int *sz, gchar * str){
	*sz = 4;
	guint digit = atoi(str);
	parr[0]=  (digit>>24)&0xff;
	parr[1]=  (digit>>16)&0xff;
	parr[2]=  (digit>>8)&0xff;
	parr[3]=  (digit)&0xff;
	return TRUE;
}

gboolean feedback_time_song(guchar *parr, int *sz, gchar * str){
	*sz = 4;
	guint digit = atoi(str);
	parr[0]=  (digit>>24)&0xff;
	parr[1]=  (digit>>16)&0xff;
	parr[2]=  (digit>>8)&0xff;
	parr[3]=  (digit)&0xff;
	return TRUE;
}


#define feddback_string(parr, sz, str){\
	gchar * pch = str;\
	while(*pch){\
		parr[*sz] = *pch;\
		pch ++;\
		(*sz) += 1;\
	}\
	parr[*sz] = '\0';\
	(*sz) += 1;\
}

gboolean feedback_cur_dirname(guchar *parr, int *sz, gchar * str){
	*sz = 0;
	feddback_string(parr, sz, str);
	return TRUE;
}

gboolean feedback_total_song(guchar *parr, int *sz, gchar * str){
	*sz = 2;
	guint digit = atoi(str);
	parr[0]=  (digit>>8)&0xff;
	parr[1]=  (digit)&0xff;
	return TRUE;
}

gboolean feedback_name(guchar *parr, int *sz, gchar * str){
	*sz = 0;
	feddback_string(parr, sz, str);
	return TRUE;
}

gboolean feedback_singer(guchar *parr, int *sz, gchar * str){
	*sz = 0;
	feddback_string(parr, sz, str);
	return TRUE;
}

gboolean feedback_ablum(guchar *parr, int *sz, gchar * str){
	*sz = 0;
	feddback_string(parr, sz, str);
	return TRUE;
}

gboolean feedback_file_names(guchar *parr, int *sz, gchar * str){
	char *end ;
	long digit = strtol(str,&end ,10);
	parr[0]=  (digit>>8)&0xff;
	parr[1]=  (digit)&0xff;
	end ++;
	*sz = 2;
	guchar * tmp = &parr[2];
	feddback_string(tmp, sz, end);
	return TRUE;
}



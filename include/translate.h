#pragma once
#include "common.h"
#include "protocol.h"
#include "base.h"
#include "message.h"

typedef struct translate_s{
	base_s * socket;
	base_s * serial;
}translate_s;

 typedef char * (*analytic_parameter_arr)(char * , guchar * , ssize_t sz);
 
 typedef gboolean (*analytic_parameter_str)(guchar *parr, int *sz, gchar * str);
  
 typedef struct arr2str_s{
	 guchar const* arrs;
	 gchar *str;
	 ssize_t len;
	 analytic_parameter_arr fn;
 }arr2str_s;
 
 typedef struct str2arr_s{
	 guchar const* arrs;
	 gchar *str;
	 ssize_t len;
	 analytic_parameter_str fn;
 }str2arr_s;

 extern arr2str_s arr2str[];
 extern str2arr_s str2arr[];

 translate_s *translate_init(base_s * socket, base_s * serial);


translate_s *translate_get();

void translate_string(translate_s *, char * string);

void translate_arr(translate_s *, guchar * arrs, guint sz);

void translate_deinit();





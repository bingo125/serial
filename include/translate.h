#pragma once
#include "common.h"
#include "protocol.h"
#include "base.h"
#include "message.h"

typedef struct translate_s{
	base * socket;
	base * serial;
}translate_s;

static translate_s *  translate = NULL;

translate_s *translate_get();

void translate_string(translate*, char * string);

void translate_arr(translate*, guchar * arrs, guint sz);



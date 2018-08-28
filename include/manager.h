#pragma once

#include "common.h"
#include "serial.h"
#include "socket.h"

typedef struct manager_s{
	base_s *socket;
	base_s *serial;
}manager_s;

void manager_init( manager_s * msg, base_s *socket, base_s *serial);
void manager_loop(manager_s * msg);
void manager_deinit( manager_s * msg);
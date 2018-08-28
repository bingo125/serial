#pragma once

#include "common.h"
#include "base.h"
#include "translate.h"

typedef struct socket_s{
	base_s base;
}socket_s;

void socket_init(socket_s * socket);

void socket_deinit(socket_s * socket);


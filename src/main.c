#include "common.h"
#include "translate.h"
#include "serial.h"
#include "socket.h"
#include "message.h"
#include "manager.h"

int main(int argc, char * argv[]){
	serial_s serial;
	socket_s socket;
	manager_s manager;
	serial_init(&serial);
	translate_init (&socket.base, &serial.base);
	socket_init(&socket);
	
	manager_init(&manager, &serial.base,&socket.base);
	
	manager_loop(&manager);
	manager_deinit(&manager);
	translate_deinit ();
	serial_deinit(&serial);
	socket_deinit(&socket);
	return 0;
}
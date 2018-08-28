#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "socket.h"

#define DEST_IP "127.0.0.1"

#define LOCAL_PORT 9990

static int socket_add(){
	struct sockaddr_in addr;
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);	 
	if (socket_fd == -1) {
	  perror("socket");
	  return -1;
	}

	addr.sin_family = AF_INET;  /* Internet地址族 */
	addr.sin_port = htons(LOCAL_PORT);	/* 端口号 */
	addr.sin_addr.s_addr=inet_addr(DEST_IP);
	bzero(&(addr.sin_zero),8);
	connect(socket_fd,(struct sockaddr*)&addr,sizeof(struct sockaddr));
	perror("---");
	assert(socket_fd > 2);
	return socket_fd;
}

void socket_base_push(void * base,void * head, ssize_t n){
	base_s * pbase = base;
	base_push(pbase, head);
}

gboolean socket_base_pop(void * base, void ** phead, int *n){
	gchar *ptr;
	base_s * pbase = base;
	if(base_get_data (pbase, (void **)&ptr)){
		translate_s *ts = translate_get ();
		translate_string (ts, ptr);
		return true;
	}
	return false;
}

void socket_init(socket_s * socket){
	int socket_fd = socket_add();
	base_init (&socket->base,socket_fd,socket_base_push, socket_base_pop,NULL);	
}


void socket_deinit(socket_s * socket){
	int socket_fd = base_get_fd (&socket->base);
	base_deinit(&socket->base);
	close(socket_fd);
}


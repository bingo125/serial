#include "manager.h"

void manager_init( manager_s * msg, base_s *socket, base_s *serial){
	msg->serial  = serial;
	msg->socket = socket;
}

void manager_deinit( manager_s * msg){
	//do nothing
}

static void handl_base_write(manager_s * pmanager, base_s * base){
	void * pdata = NULL;
	int len = 0;;
	while(base->pop(base, &pdata, &len)){
		if(write(base_get_fd(base),pdata,len)  == -1){
			perror("");
		}
		base->clear(base,pdata);
	}
}

void manager_loop(manager_s * pmanager){
	gint socket_fd = base_get_fd(pmanager->socket);
	gint serial_fd = base_get_fd(pmanager->serial);
	gint max_fd = (socket_fd >serial_fd ? socket_fd: serial_fd);
	gboolean quit = false;
	char buf[BUFSIZ]  = {};
	fd_set fds;
	FD_ZERO(&fds);
    FD_SET(socket_fd, &fds);
    FD_SET(serial_fd, &fds);
	struct timeval time_lapse;
	while (!quit) {
		fd_set tmp_fds = fds;
		time_lapse.tv_sec = 0;
		time_lapse.tv_usec = 50*1000;
		switch (select(max_fd + 1, &tmp_fds, NULL, NULL, &time_lapse)) {
		case 0:
		    //                printf(" time is time_lapse and try again \n");
		    handl_base_write(pmanager, pmanager->socket);
		    //此处后续做一些延时
		    handl_base_write(pmanager, pmanager->serial);
		    break;
		case -1:
			perror(" xxxxxx");
			quit = true;
		    break;
		default:{
	        base_s *act_event_source;
	        if(FD_ISSET(serial_fd, &tmp_fds)){
	        	act_event_source = pmanager->serial;
	        }else if(FD_ISSET(socket_fd, &tmp_fds)){
	        	act_event_source = pmanager->socket;
	        }else{
	        	perror(" nothing happend here");
	        	continue;
	        }
	        int len = 0;
	        ioctl(base_get_fd(act_event_source), FIONREAD, &len);
	        if(len == 0){
	        	quit = true;
	        	continue;
	        }
	        len = read(base_get_fd(act_event_source),buf, BUFSIZ);
	        act_event_source->push(act_event_source, buf, len);
	        }
		
	   }
   }
}


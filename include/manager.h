#pragma once

#include "common.h"
#include "serial.h"
#include "socket.h"

typedef struct manager_s{
	base_s *socket;
	base_s *serial;
};

static handl_base_write(manager_s * pmanager, base_s * base){
	char * pdata = NULL;
	int len = 0;;
	while(base->pop(base, &pdata, &len)){
		if(write(base_get_fd(base),pdata, pdata,len)  == -1){
			perror("");
		}
		base->clear(base,pdata);
	}
}

void manager_loop(manager_s * pmanager){
	gint socket_fd = base_get_fd(socket);
	gint serial_fd = base_get_fd(serial);
	gint max_fd = (socket_fd >serial_fd ? socket_fd: serial_fd);
	gboolean quit = false;
	char buf[BUFSIZ]  = {};
	struct timeval time_lapse;
	struct time_val 
	   while (!quit) {
        fd_set tmp_fds = fds;
        time_lapse.tv_sec = 0;
        time_lapse.tv_usec = 50*1000*;
        switch (select(maxfd + 1, &socket_fd, NULL, NULL, &time_lapse)) {
        case 0:
            //                printf(" time is time_lapse and try again \n");
            handl_base_write(pmanager, pmanager->socket);
            handl_base_write(pmanager, pmanager->serial);
            break;
        case -1:
        	perror(" xxxxxx");
        	quit = true;
            break;
        default:
            if (FD_ISSET(usb_monitor->listen_socket, &tmp_fds)) {
                client_fd =
                     accept(usb_monitor->listen_socket, (struct sockaddr *) &cliaddr, (socklen_t *) &addrlen);
                for (i = 0; i < FD_SIZE; i++) {
                    if (usb_monitor->client[i] == -1) {
                        usb_monitor->client[i] = client_fd;
                        FD_SET(client_fd, &fds);
                        if (client_fd > maxfd) {
                            maxfd = client_fd;
                        }
                        break;
                    }
                }
                if (i == FD_SIZE) {
                    close(client_fd);
                    // 链接端口太多
                }
       
            } else {
                for (i = 0; i < FD_SIZE; i++) {
                    if (usb_monitor->client[i] == -1){
                    // 此处有内存泄露，但是问题不大，正常连接过程中，socket会一直建立，泄露只有几个字节而已。
                    	continue;
                    }
                    base *act_event_source;
                   
                    if(FD_ISSET(serial_fd, &tmp_fds)){
                    	act_event_source = serial_s;
                    }else {
                    	act_event_source = socket_fd;
                    }
                    int len = 0;
                    ioctl(base_get_fd(act_event_source), FIONREAD, &len);
                    if(len == 0){
                    	quit = true;
                    }
                    len = read(base_get_fd(act_event_source),buf, BUFSIZ);
                    act_event_source->push(act_event_source, 
                    	act_event_source != socket ? socket : serial, len);
                }
            }
        }
    }
}
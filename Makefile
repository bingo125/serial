PHONY: serial clean
srcs=$(wildcard ./src/*.c)
all_srcs=$(wildcard ./src/*.c ./include/*.h)
objs=$(srcs:%.c=%.o)
CFLAGS=-Wall -Werror -g -I./include/  -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -std=gnu11 -g
LDLIBS=-lglib-2.0
depends=${wild %c %o ${srcs}}
$(patsubst %.c,%.o,$(wildcard *.c))
all: serial
	@echo $(srcs)
	@echo $(objs)

dos2unix:
	@dos2unix $(all_srcs) 

codeline:
	wc -l $(all_srcs) 

serial:$(objs) 
	cc $^  $(LDLIBS) -o $@
clean:
	rm $(objs)


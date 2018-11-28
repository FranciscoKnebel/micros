TARGET=p2
SRCS=$(TARGET).c

FLAGS=-Wall -g -MMD
INCLUDE=-I. -I../include
LIBDIR=-L../lib
LIBS=-lgalileo2

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o) ../lib/libgalileo2.a
	$(CC) -lm -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

install: $(TARGET)
	-ssh root@galileo6 "groupadd -r p2"
	-ssh root@galileo6 "groupmems -g p2 -a micros"
	scp p2_init root@galileo6:/etc/init.d
	ssh root@galileo6 "chmod +x /etc/init.d/p2_init"
	-ssh root@galileo6 "update-rc.d p2_init defaults"
	-ssh root@galileo6 "mkdir /home/micros/p2"
	scp p2 root@galileo6:~
	ssh root@galileo6 "chmod +x p2"
	ssh root@galileo6 "cp p2 /home/micros/p2"
	ssh root@galileo6 "rm ~/p2"
	-ssh root@galileo6 "reboot"
	
clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)

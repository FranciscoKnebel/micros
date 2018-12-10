TARGET1=tx
SRCS1=$(TARGET1).c

TARGET2=rx
SRCS2=$(TARGET2).c

TARGETLIB=libgalileo2.a
LIBSRCS=lib/pputs.c lib/pgets.c lib/i2c_write_reg.c

TARGETS=$(TARGET1) $(TARGET2)

FLAGS=-Wall -MMD -g
INCLUDE=-I. -I./include
LIBDIR=
LIBS=$(TARGETLIB)

CC=$(CROSS_COMPILE)gcc
CCAR=$(CROSS_COMPILE)ar
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)
CCARFLAGS=-crvs

all: $(TARGETLIB) $(TARGETS)
	@echo "All compilation completed. Sending to remote..."
	scp *x micros@galileo13:

$(TARGETLIB): $(LIBSRCS:.c=.o)
	$(CCAR) $(CCARFLAGS) $@ $^
	@echo "Lib compilation completed."
	
$(TARGETS) : % : %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d $(LIBSRCS:.c=.o) $(LIBSRCS:.c=.d)

distclean: clean
	rm -f $(TARGETS) $(TARGETLIB)

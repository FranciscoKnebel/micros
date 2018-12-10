TARGET=printuppercase
CSRCS=$(TARGET).c 
ASMSRCS=printup.s

FLAGS=
INCLUDE=-I.
LIBDIR=-L../lib
LIBS=-leng10032

AS=$(CROSS_COMPILE)as
ASFLAGS=-gstabs -a=`echo $@ | cut -f 1 -d.`.lst --32 \
	-MD=`echo $@ | cut -f 1 -d.`.d
CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -MMD $(INCLUDE) -g -m32
LDFLAGS=-m32 $(LIBDIR) $(LIBS)

all: ../lib/eng10032 $(TARGET)

../lib/eng10032:
	make -C ../lib

$(TARGET): $(CSRCS:.c=.o) $(ASMSRCS:.s=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<
	
-include $(ASMSRCS:.s=.d)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(CSRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d *.lst

distclean: clean
	rm -f $(TARGET)
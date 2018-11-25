TARGET=main
SRCS=src/$(TARGET).c

DOXYGENCONFIG=doxygen.config

FLAGS=-O2 -Wall -g -MMD
INCLUDE=-I. -I../include
LIBDIR=-L../lib
LIBS=

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak
	rm **/*.o **/*.d

distclean: clean
	rm -f $(TARGET)

docs: $(SRCS)
	rm -rf docs/
	doxygen ${DOXYGENCONFIG}

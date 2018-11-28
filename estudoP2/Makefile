# Main target program
TARGET = main
TARGET_SRC = src/$(TARGET).c
TARGET_OBJ = $(TARGET_SRC:.c=.o)

# List of module files
# MODULE_LIST contains the space-separated module list.
# MODULE_SRCS contains the MODULE_LIST items with .c suffix and src/ prefix.
MODULE_LIST = 
MODULE_SRCS = $(addsuffix .c, $(addprefix src/, ${MODULE_LIST}))
MODULE_OBJS = $(MODULE_SRCS:.c=.o)

DOXYGENCONFIG=Doxyfile
FLAGS=-O2 -Wall -g -MMD
INCLUDE=-I. -I./include
LIBDIR=-L./lib
LIBS=-lgalileo2

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

.PHONY: all
all: $(TARGET)
	@echo "Build finished."

$(TARGET): $(MODULE_OBJS) $(TARGET_OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(TARGET_SRC:.c=.d)

clean:
	rm -f *~ *.bak
	rm $(TARGET) $(TARGET_OBJ) $(TARGET_OBJ:.o=.d) $(MODULE_OBJS) $(MODULE_OBJS:.o=.d)

docs: Doxyfile DoxygenLayout.xml README.md LICENSE.md $(TARGET)
	@echo "Building Doxygen..."
	doxygen ${DOXYGENCONFIG}

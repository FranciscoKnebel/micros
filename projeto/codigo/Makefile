# Main target program
TARGET = quanser_controller
TARGET_SRC = src/$(TARGET).c
TARGET_OBJ = $(TARGET_SRC:.c=.o)

TARGET2 = quanser_pwm
TARGET2_SRC = src/$(TARGET2).c
TARGET2_OBJ = $(TARGET2_SRC:.c=.o)

TARGET3 = quanser_motor
TARGET3_SRC = src/$(TARGET3).c
TARGET3_OBJ = $(TARGET3_SRC:.c=.o)

TARGET4 = quanser_elbow
TARGET4_SRC = src/$(TARGET4).c
TARGET4_OBJ = $(TARGET4_SRC:.c=.o)

TARGET_LIST = $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4)

# List of module files
# MODULE_LIST contains the space-separated module list.
# MODULE_SRCS contains the MODULE_LIST items with .c suffix and src/modules prefix.
MODULE_LIST = decoder pwm spi h_bridge
MODULE_SRCS = $(addsuffix .c, $(addprefix src/modules/, ${MODULE_LIST}))
MODULE_OBJS = $(MODULE_SRCS:.c=.o)

# Build target machine to send compiled program
BUILD_TARGET = galileo11

DOXYGENCONFIG=Doxyfile
FLAGS=-O2 -Wall -g -MMD
INCLUDE=-I. -I./include
LIB_DIR=-L./lib
LIB_LIST=galileo2
LIBS=$(addprefix -l, ${LIB_LIST})

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIB_DIR) $(LIBS)

.PHONY: all
all: $(TARGET_LIST)
	@echo "Build finished."

$(TARGET): $(MODULE_OBJS) $(TARGET_OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

$(TARGET2): $(MODULE_OBJS) $(TARGET2_OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

$(TARGET3): $(MODULE_OBJS) $(TARGET3_OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

$(TARGET4): $(MODULE_OBJS) $(TARGET4_OBJ) 
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(TARGET_SRC:.c=.d)

clean:
	rm -f *~ *.bak
	rm src/**/*.d src/**/*.o
	rm ${TARGET_LIST}

docs: Doxyfile DoxygenLayout.xml README.md LICENSE.md $(TARGET_LIST)
	@echo "Building Doxygen..."
	doxygen ${DOXYGENCONFIG}

send: all
	scp quanser_* micros@$(BUILD_TARGET):
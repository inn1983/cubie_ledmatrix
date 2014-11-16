CROSS_COMPILE=
CC= $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip
AR = $(CROSS_COMPILE)ar

INCLUDES:=$(foreach dir,$(SRCDIRS),-I$(dir)) 
CFLAGS += -Wall -DOS_LINUX -O2 -g $(INCLUDES)
SRCDIRS:=.
SRC := $(wildcard *.c) $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJ := $(SRC:%.c=%.o) $(SRCC:%.cpp=%.o)

TARGET := cubie_ledmatrix
.PHONY : clean all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) -lrt
#	$(STRIP) $@

clean:
	@rm -f $(TARGET)
	@rm -f $(OBJ)


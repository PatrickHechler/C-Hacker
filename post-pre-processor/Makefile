PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LDFLAGS = 

CC = gcc

AR = ar

CFLAGS = -fPIC

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g -Og
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -Ofast -O10
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

BIN_ROOT = $(PROJECT_ROOT)binary/

BIN = $(BIN_ROOT)$(BUILD_MODE)/

SOURCE = $(PROJECT_ROOT)src/

TARGET = $(BIN_ROOT)post-pre-processor

OBJS = $(BIN)post-pre-processor.o

all:	INIT $(TARGET)

INIT:
	echo build mode: $(BUILD_MODE)
	mkdir -p $(PROJECT_ROOT)exports/
	mkdir -p $(BIN)

$(TARGET):	$(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)
	ln --symbolic --force $(TARGET) $(PROJECT_ROOT)exports/post-pre-processor

$(BIN)%.o:	$(SOURCE)%.c
	$(CC) -x c -c $(CFLAGS) -o $@ $<

clean:
	rm -frd $(BIN_ROOT)

PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LDFLAGS = 

CHECKLDFLAGS = 

EXELDFLAGS = 

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

LIB_BIN = $(BIN)lib/

EXE_BIN = $(BIN)exe/

CHECK_BIN = $(BIN)checks/

SOURCE = $(PROJECT_ROOT)src/

LIB_SRC = $(SOURCE)lib/

EXE_SRC = $(SOURCE)exe/

CHECK_SRC = $(SOURCE)checks/

TARGET_EXE = $(BIN_ROOT)c-hacker

TARGET_A = $(BIN_ROOT)libc-hacker.a

TARGET_SO = $(BIN_ROOT)libc-hacker.so

CHECK_TARGET = $(CHECK_BIN)c-hacker-checks

EXE_OBJS = $(EXE_BIN)c-hacker.o

LIB_OBJS = $(LIB_BIN)c-hacker.o

CHECK_OBJS = $(CHECK_BIN)c-hacker-checks.o

all:	INIT $(CHECK_TARGET) $(TARGET_A) $(TARGET_SO) $(TARGET_EXE)
	$(TARGET_EXE) $(CHECK_TARGET)

exe: INIT $(TARGET_EXE)

static: INIT $(TARGET_A)

shared: INIT $(TARGET_SO)

INIT:
	echo build mode: $(BUILD_MODE)
	mkdir -p $(PROJECT_ROOT)testout/

INIT_CHECK:
	mkdir -p $(CHECK_BIN)

INIT_EXE:
	mkdir -p $(EXE_BIN)

INIT_LIB:
	mkdir -p $(LIB_BIN)

$(CHECK_TARGET):	INIT_CHECK $(CHECK_OBJS)
	$(CC) -shared -o $@ $(LDFLAGS) $(CHECK_OBJS)

$(TARGET_EXE):	INIT_EXE $(EXE_OBJS)
	$(CC) $(EXELDFLAGS) -o $(TARGET_EXE) $(EXE_OBJS)

$(TARGET_SO):	INIT_LIB $(LIB_OBJS)
	$(CC) -shared -o $@ $(LDFLAGS) $(LIB_OBJS)

$(TARGET_A):	INIT_LIB $(LIB_OBJS)
	$(AR) -rc $@ $(OBJS)

$(BIN)%.o:	$(SOURCE)%.c
	$(CC) -x c -c $(CFLAGS) -o $@ $<

clean:
	rm -frd $(PROJECT_ROOT)testout/ $(BIN_ROOT)

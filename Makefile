PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LDFLAGS = 

CHECKLDFLAGS = 

EXELDFLAGS = -ldl

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

EXP = $(PROJECT_ROOT)exports/

BIN_ROOT = $(PROJECT_ROOT)binary/

BIN = $(BIN_ROOT)$(BUILD_MODE)/

EXE_BIN = $(BIN)exe/

LIB_BIN = $(BIN)lib/

CHECK_BIN = $(BIN)check/

SOURCE = $(PROJECT_ROOT)src/

LIB_SRC = $(SOURCE)lib/

EXE_SRC = $(SOURCE)exe/

CHECK_SRC = $(SOURCE)check/

CHECK_SRC_FILE = $(CHECK_SRC)checks.c

TARGET_EXE = $(BIN_ROOT)c-hacker

TARGET_A = $(BIN_ROOT)libc-hacker.a

TARGET_SO = $(BIN_ROOT)libc-hacker.so

EXE_OBJS = $(EXE_BIN)c-hacker.o

LIB_OBJS = $(LIB_BIN)c-hacker.o

all:	INIT check static shared exe

exe: INIT $(TARGET_EXE)

static: INIT exe $(TARGET_A)

shared: INIT exe $(TARGET_SO)

check: INIT_CHECK shared exe
	echo check now
	$(TARGET_EXE) --no-include --no-exe '--func-pre=extern void ' $(CHECK_SRC_FILE) $(CHECK_BIN)
	$(TARGET_EXE) --check=$(CHECK_BIN)checks

INIT:
	echo build mode: $(BUILD_MODE)
	mkdir -p $(EXP)

INIT_CHECK:
	mkdir -p $(CHECK_BIN)

INIT_EXE:
	mkdir -p $(EXE_BIN)
	mkdir -p $(EXP)exe/

INIT_LIB:
	mkdir -p $(LIB_BIN)
	ln --symbolic --force $(SOURCE)include/ $(EXP)include

INIT_SO: INIT_LIB
	mkdir -p $(EXP)shared/
	
INIT_A: INIT_LIB
	mkdir -p $(EXP)static/

$(TARGET_EXE):	INIT_EXE $(EXE_OBJS)
	echo make target: exe
	$(CC) $(EXELDFLAGS) -o $(TARGET_EXE) $(EXE_OBJS)
	ln --symbolic --force $(TARGET_EXE) $(EXP)exe/c-hacker

$(TARGET_SO):	INIT_SO $(LIB_OBJS)
	echo make target: shared
	$(CC) -shared -o $@ $(LDFLAGS) $(LIB_OBJS)
	ln --symbolic --force $(TARGET_SO) $(EXP)shared/libc-hacker.so

$(TARGET_A):	INIT_A $(LIB_OBJS)
	echo make target: static
	$(AR) -rc $@ $(LIB_OBJS)
	ln --symbolic --force $(TARGET_SO) $(EXP)static/libc-hacker.a

$(BIN)%.o:	$(SOURCE)%.c
	echo compile source file $<
	$(CC) -x c -c $(CFLAGS) -o $@ $<

clean:
	rm -frd $(PROJECT_ROOT)testout/ $(BIN_ROOT) $(EXP)

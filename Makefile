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

EXP = $(PROJECT_ROOT)exports/

BIN_ROOT = $(PROJECT_ROOT)binary/

BIN = $(BIN_ROOT)$(BUILD_MODE)/

EXE_BIN = $(BIN)exe/

GEN_BIN = $(BIN)generated/

CHECK_BIN = $(BIN)checks/

SOURCE = $(PROJECT_ROOT)src/

LIB_SRC = $(SOURCE)lib/

GEN_SRC = $(SOURCE)generated/

EXE_SRC = $(SOURCE)exe/

CHECK_SRC = $(SOURCE)checks/

CHECK_SRC_FILE = $(CHECK_SRC)c-hacker-checks.c

TARGET_EXE = $(BIN_ROOT)c-hacker

TARGET_A = $(BIN_ROOT)libc-hacker.a

TARGET_SO = $(BIN_ROOT)libc-hacker.so

EXE_OBJS = $(EXE_BIN)c-hacker.o

LIB_SOURCE_FILE = $(LIB_SRC)c-hacker.c

LIB_GENERATED_FILE = $(GEN_SRC)c-hacker.c

LIB_GENERATED_OBJ_FILE = $(GEN_BIN)c-hacker.o

all:	INIT check static shared exe
	$(TARGET_EXE) $(CHECK_TARGET)

exe: INIT $(TARGET_EXE)

static: INIT exe $(TARGET_A)

shared: INIT exe $(TARGET_SO)

check: INIT shared exe
	$(TARGET_EXE) --no-include "--func-pre=extern " $(CHECK_SRC_FILE) $(CHECK_BIN)

INIT:
	echo build mode: $(BUILD_MODE)
	mkdir -p $(EXP)
	ln --symbolic --force $(PROJECT_ROOT)include/ $(EXP)include

INIT_CHECK:
	mkdir -p $(CHECK_BIN)

INIT_EXE:
	mkdir -p $(EXE_BIN)
	mkdir -p $(EXP)exe/

INIT_LIB:
	mkdir -p $(LIB_BIN)
	mkdir -p $(GEN_SRC)

INIT_SO: INIT_LIB
	mkdir -p $(EXP)shared/
	
INIT_A: INIT_LIB
	mkdir -p $(EXP)static/

$(TARGET_EXE):	INIT_EXE $(EXE_OBJS)
	$(CC) $(EXELDFLAGS) -o $(TARGET_EXE) $(EXE_OBJS)
	ln --symbolic --force $(TARGET_EXE) $(EXP)exe/c-hacker

$(CHECK_TARGET):	INIT_CHECK $(CHECK_OBJS) $(TARGET_SO)
	$(CC) -o $@ $(CHECKLDFLAGS) $(CHECK_OBJS)

$(LIB_GENERATED_FILE): 
	$(TARGET_EXE) --no-include --gen-obj '--func-pre=extern ' $(CHECK_SRC_FILE) $(CHECK_BIN)

$(TARGET_SO):	INIT_SO $(LIB_GENERATED_OBJ_FILE)
	$(CC) -shared -o $@ $(LDFLAGS) $(LIB_GENERATED_OBJ_FILE)
	ln --symbolic --force $(TARGET_SO) $(EXP)shared/libc-hacker.so

$(TARGET_A):	INIT_A $(LIB_GENERATED_FILE)
	$(AR) -rc $@ $(LIB_GENERATED_OBJ_FILE)
	ln --symbolic --force $(TARGET_SO) $(EXP)static/libc-hacker.a

$(BIN)%.o:	$(SOURCE)%.c
	$(CC) -x c -c $(CFLAGS) -o $@ $<

clean:
	rm -frd $(PROJECT_ROOT)testout/ $(BIN_ROOT) $(EXP)

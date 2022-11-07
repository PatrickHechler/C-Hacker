PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

LDFLAGS = 

CHECKLDFLAGS = 

EXELDFLAGS = -ldl -L$(EXP)shared/ -lc-hacker

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

PPP = $(PROJECT_ROOT)post-pre-processor/exports/post-pre-processor

EXP = $(PROJECT_ROOT)exports/

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

CHECK_TARGET = $(CHECK_BIN)c-hacker-checks.so

EXE_OBJS = $(EXE_BIN)c-hacker.o

LIB_OBJS = $(LIB_BIN)c-hacker.o

CHECK_OBJS = $(CHECK_BIN)c-hacker-checks.o

all:	INIT $(PPP) check static shared exe
	$(TARGET_EXE) $(CHECK_TARGET)

exe: INIT $(PPP) $(TARGET_EXE)

static: INIT $(PPP) $(TARGET_A)

shared: INIT $(PPP) $(TARGET_SO)

check: INIT shared $(PPP) $(CHECK_TARGET)

INIT:
	echo build mode: $(BUILD_MODE)
	mkdir -p $(EXP)
	ln --symbolic $(PROJECT_ROOT)include/ $(EXP)include

INIT_CHECK:
	mkdir -p $(CHECK_BIN)

INIT_EXE:
	mkdir -p $(EXE_BIN)
	mkdir -p $(EXP)exe/

INIT_LIB:
	mkdir -p $(LIB_BIN)
	mkdir -p $(EXP)shared/
	mkdir -p $(EXP)static/

$(PPP):
	make -C $(PROJECT_ROOT)post-pre-processor/ all

$(CHECK_TARGET):	INIT_CHECK $(CHECK_OBJS) $(TARGET_SO)
	$(CC) -shared -o $@ $(CHECKLDFLAGS) $(CHECK_OBJS)

$(TARGET_EXE):	INIT_EXE $(EXE_OBJS)
	$(CC) $(EXELDFLAGS) -o $(TARGET_EXE) $(EXE_OBJS)

$(TARGET_SO):	INIT_LIB $(LIB_OBJS)
	$(CC) -shared -o $@ $(LDFLAGS) $(LIB_OBJS)
	ln --symbolic $(TARGET_SO) $(EXP)shared/libc-hacker.so

$(TARGET_A):	INIT_LIB $(LIB_OBJS)
	$(AR) -rc $@ $(OBJS)
	ln --symbolic $(TARGET_SO) $(EXP)static/libc-hacker.a

$(BIN)%.o:	$(SOURCE)%.c
	$(CC) -x c -c $(CFLAGS) -o $@ $<

$(BIN)%.o:	$(SOURCE)%-.c # $(SOURCE)%-.c_
	$(CC) -x c -E $(CFLAGS) -o $@.c $<
	cp -T $<_ $@.c.c
	$(PPP) < $@.c >> $@.c.c
	$(CC) -x c -c $(CFLAGS) -o $@ $@.c.c

clean:
	rm -frd $(PROJECT_ROOT)testout/ $(BIN_ROOT) $(EXP)
	make -C ./post-pre-processor/ clean

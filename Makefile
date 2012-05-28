PREFIX=.

BIN=testglib

LIBPATH=
INCLUDE_PATH=
THIRD_PARTY_PATH=../o2oserver/third_party/Linux

#GLIB_PATH=$(THIRD_PARTY_PATH)
GLIB_PATH=/home/zhangjun-s/opt/glib
EVENT_PATH=

GLIB_CFLAGS=-I$(GLIB_PATH)/include/glib-2.0 -I$(GLIB_PATH)/lib/glib-2.0/include
GLIB_LIBS=-L$(GLIB_PATH)/lib -lglib-2.0
GTHREAD_LIBS=-pthread -lgthread-2.0 -lrt -lglib-2.0

EVENT_LIBS=-L$(EVENT_PATH)/lib -levent
EVENT_CFLAGS=-I$(EVENT_PATH)/include

LIBS:=$(GLIB_LIBS) $(GTHREAD_LIBS) #$(EVENT_LIBS)

INCLUDE=$(GLIB_CFLAGS) 

CFLAGS= -std=gnu99 -g -Wall $(INCLUDE)

INSTALL=/usr/bin/install -c

#LDFLAGS= -Wl,-R$(THIRD_PARTY_PATH)/lib
LDFLAGS= -Wl,-R$(GLIB_PATH)/lib

CC=gcc

SOURCE=testglib.c
OBJS:=$(patsubst %.c, %.o, $(SOURCE))
DEPS:=$(patsubst %.o, %.d, $(OBJS))

CPPFLAGS += -MMD

.PHONY: all deps objs clean

all: $(BIN)

deps: $(DEPS)

objs: $(OJBS)

-include $(DEPS)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -g -o $(BIN) $(OBJS) $(LIBS)
		
clean:
	@$(RM) $(OBJS) $(DEPS) $(BIN)

test:
	./$(BIN)

install:
	if test ! -d $(PREFIX)/bin;then mkdir -p $(PREFIX)/bin;fi
	$(INSTALL) $(BIN) $(PREFIX)/bin/


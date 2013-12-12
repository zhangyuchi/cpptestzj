# makefile for libmark 

LIBVER = 1.0.0
LIBVER_MAJOR = $(shell echo $(LIBVER) | cut -d. -f1)


CXX11_HOME = /home/zhangjun-s/opt/gcc

CXXFLAGS := \
    -g3 \
    -std=c++11 \
    -fPIC \
    -Wall \
    -Wextra \
    -time \
    -Wno-parentheses \
    -Wdeprecated-declarations \
    -fmerge-all-constants \
    -I $(CXX11_HOME)/include 

RELEASE_FLAGS := \
	-O3 \
    -DDTREE_ICASE \
	-DNDEBUG

DEBUG_FLAGS := \
    -O0 \
    -D__DEBUG 

LDFLAGS += \
	-static-libstdc++ -static-libgcc \
    -fmerge-all-constants \
	-L${CXX11_HOME}/lib64 

LIBS := \
	-lpthread \
	-lrt 

DIR := . 
SRC := $(foreach d, $(DIR), $(wildcard $(d)/*.cpp))

RELEASE_OBJ := $(patsubst %.cpp, %.o, $(SRC))
DEBUG_OBJ := $(patsubst %.cpp, %.d.o, $(SRC))

CXX := ${CXX11_HOME}/bin/g++

LD_LIBRARY_PATH=/home/zhangjun-s/opt/gcc/lib:/home/zhangjun-s/opt/gcc/lib64:$(DEFAULT_LIB_INSTALL_PATH)

all: thread  

%.o : %.cpp
	$(CXX) -c $^ $(CXXFLAGS) $(RELEASE_FLAGS) -o $@

%.d.o : %.cpp
	$(CXX) -c $^ $(CXXFLAGS) $(DEBUG_FLAGS) -o $@

thread : thread.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

lambda : lambda.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

future : future.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

feature : feature.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)


clean:
	rm -rf *.o *.exe 

.PHONY : 


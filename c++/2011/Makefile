# makefile for libmark 

LIBVER = 1.0.0
LIBVER_MAJOR = $(shell echo $(LIBVER) | cut -d. -f1)


CXX11_HOME = /home/zhangjun-s/opt/gcc
#CXX11_HOME = /home/leipeng/opt

CXXFLAGS := \
    -g3 \
    -std=c++11 \
    -fPIC \
    -Wall \
    -Wextra \
    -time \
    -Wno-parentheses \
    -Wdeprecated-declarations \
    -I $(CXX11_HOME)/include 

    #-fmerge-all-constants 

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

CXX := export LD_LIBRARY_PATH=${CXX11_HOME}/lib; ${CXX11_HOME}/bin/g++

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

queen : queen.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

huarongdao : huarongdao.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

weird : weird.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

meta : meta.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

branchpredict : branchpredict.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)



clean:
	rm -rf *.o *.exe 

.PHONY : 


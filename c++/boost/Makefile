# makefile for libmark 

LIBVER = 1.0.0
LIBVER_MAJOR = $(shell echo $(LIBVER) | cut -d. -f1)


CXX11_HOME = /home/zhangjun-s/opt/gcc
CXX11_HOME = /home/leipeng/opt

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

CXX := export LD_LIBRARY_PATH=${CXX11_HOME}/lib; ${CXX11_HOME}/bin/g++

all: thread  

%.o : %.cc
	$(CXX) -c $^ $(CXXFLAGS) $(RELEASE_FLAGS) -o $@

%.d.o : %.cc
	$(CXX) -c $^ $(CXXFLAGS) $(DEBUG_FLAGS) -o $@

boost : testboost.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

variant : testvariant.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

any : testany.d.o
	$(CXX) $^ -o $@.exe $(LDFLAGS) $(LIBS)

clean:
	rm -rf *.o *.exe 

.PHONY : 


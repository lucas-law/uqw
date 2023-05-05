CC  ?= gcc
CXX ?= g++

target := test
srcs  = main.o
srcs += unqlite.o

workdir = $(shell pwd)

CXXFLAGS += -std=c++11

#CXXFLAGS += -I $(workdir)
#CXXFLAGS += --coverage

#LDFLAGS += --coverage

.PHONY : all clean distclean

all : $(target)

$(target) : $(srcs)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean distclean :
	-rm -f $(srcs)
	-rm -f $(target)

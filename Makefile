######################################################
# This Makefile for build free getopts library       #
#                                                    #
# Author: Nestor B. Zubekhin                         #
# See LICENSE file for copyright and license details #
######################################################

CC	    	= gcc
CXX         = g++
AR	    	= ar
CCFLAGS		= -O3
ARFLAGS		= cr

OBJECTS1	= src/fgetopt.o
LIB1		= fgetopt.a
OBJECTS2	= examples/use_fgetopt_cpp.o
PRG1		= use_fgetopt_cpp
OBJECTS3	= examples/use_fgetopt_alias_cpp.o
PRG2		= use_fgetopt_alias_cpp
OBJECTS4	= examples/use_fgetopt_c.o
PRG3		= use_fgetopt_c
OBJECTS5	= examples/use_fgetopt_alias_c.o
PRG4		= use_fgetopt_alias_c

INCLIB      = -lfgetopt
INCLUDES    = -I/usr/include/ -I./src/
LIBDIR      = -L./src/

RM		    = rm -f

all: $(LIB1) $(PRG1) $(PRG2) $(PRG3) $(PRG4)

$(LIB1): $(OBJECTS1)
	$(AR) $(ARFLAGS) src/lib$(LIB1) $(OBJECTS1)

$(PRG1): $(OBJECTS2)
	$(CXX) $(OBJECTS2) $(LIBDIR) $(INCLIB) -o examples/$@

$(PRG2): $(OBJECTS3)
	$(CXX) $(OBJECTS3) $(LIBDIR) $(INCLIB) -o examples/$@

$(PRG3): $(OBJECTS4)
	$(CXX) $(OBJECTS4) $(LIBDIR) $(INCLIB) -o examples/$@

$(PRG4): $(OBJECTS5)
	$(CXX) $(OBJECTS5) $(LIBDIR) $(INCLIB) -o examples/$@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cc
	$(CXX) $(CCFLAGS) $(INCLUDES) -c $< -o $@

src/fgetopt.o: src/fgetopt.c
examples/use_fgetopt_cpp.o: examples/use_fgetopt_cpp.cc
examples/use_fgetopt_alias_cpp.o: examples/use_fgetopt_alias_cpp.cc
examples/use_fgetopt_c.o: examples/use_fgetopt_c.c
examples/use_fgetopt_alias_c.o: examples/use_fgetopt_alias_c.c

clean:
	$(RM) *~ *.err src/*.o src/lib$(LIB1) examples/*.o \
    examples/$(PRG1) examples/$(PRG2) examples/$(PRG3) examples/$(PRG4)

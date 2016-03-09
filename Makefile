# Evolver - "Dawkins Weasel" genetic algorithm Makefile
#
# By Jaldhar H. Vyas <jaldhar@braincells.com>
# 
# (C) 2016 Consolidated Braincells Inc.  All rights reserved.
# "Do What Thou Wilt" Shall Be The Whole Of The License.

.POSIX:

CXX=c++
CXXFLAGS=-std=c++11 -O2 -g -Wall -Wextra -Wcast-qual -Wformat=2
LDFLAGS=

HEADERS=evolver.h
OBJECTS=evolver.o weasel.o
PROGRAM=weasel

INSTALL=/usr/bin/install
PREFIX=/usr/local
DESTDIR=

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	
%.o: %.cc $(HEADERS) 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

install: $(PROGRAM)
	if [ ! -e $(DESTDIR)$(PREFIX)/bin ]; then \
		$(INSTALL) -d -oroot -groot -m0755 $(DESTDIR)$(PREFIX)/bin; \
	fi 
	$(INSTALL) -s -m0755 -oroot -groot $(PROGRAM) $(DESTDIR)$(PREFIX)/bin

memcheck: $(PROGRAM)
	valgrind --leak-check=full -v ./$(PROGRAM)

clean:
	-rm *.o

distclean: clean
	-rm $(PROGRAM)

,PHONY: clean distclean install

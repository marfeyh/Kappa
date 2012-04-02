SRCPATH = ../../src
SRCOBJS = $(wildcard $(SRCPATH)/*.o)
TESTSRCS = $(wildcard *.c)

check: testsuite
	@echo Running tests...
	./testsuite

gcovcheck: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovcheck: check
	gcov testsuite
	cd $(SRCPATH) && gcov pressure.c

gcovcheckb: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovcheckb: check
	gcov -b -c testsuite
	cd $(SRCPATH) && gcov -b -c pressure.c

memcheck: EXTRAGCCFLAGS+= -g
memcheck: testsuite
	@echo Running tests under valgrind...
	valgrind --leak-check=full ./testsuite 

testsuite.o: $(TESTSRCS)
	gcc -c checkmain.c -o testsuite.o $(EXTRAGCCFLAGS) -I $(SRCPATH)

conversion_test.o: conversion_test.c conversion_test.h
	gcc -c conversion_test.c -o conversion_suite.o $(EXTRAGCCFLAGS) -I $(SRCPATH)

testsuite: $(SRCOBJS) testsuite.o conversion_test.o
	gcc $(SRCOBJS) testsuite.o conversion_suite.o -o testsuite $(EXTRAGCCFLAGS) -lcheck

clean:
	rm -f testsuite testsuite.exe testsuite.o *.gcov *.gcda *.gcno

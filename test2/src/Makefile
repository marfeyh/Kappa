conversion: conversion.h conversion.c  pressure.h conversion.c main.c
	gcc -o conversion conversion.c pressure.c main.c -I. $(EXTRAGCCFLAGS)

testobjs: conversion.o pressure.o

conversion.o: conversion.h conversion.c  
	gcc -o conversion.o -c conversion.c $(EXTRAGCCFLAGS)

pressure.o: pressure.h pressure.c
	gcc -o pressure.o -c pressure.c $(EXTRAGCCFLAGS)

testobjscov: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
testobjscov: testobjs

testobjsgdb: EXTRAGCCFLAGS+= -g
testobjsgdb: testobjs

gdb: EXTRAGCCFLAGS+= -g
gdb: conversion

gcovcalc: EXTRAGCCFLAGS+= -fprofile-arcs -ftest-coverage
gcovcalc: conversion

clean:
	rm -f conversion conversion.exe conversion.o *.gcov *.gcda *.gcno

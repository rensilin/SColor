CC=g++
CCFLAGS=-std=c++11
CCF=${CC} ${CCFLAGS}

test:test.o SColor.o
	${CCF} -o $@ $^

test.o:test.cpp
	${CCF} -c $<

SColor.o:SColor.cpp SColor.h
	${CCF} -c $<

run:test
	./test

clear:
	rm -rf *.o
	rm test

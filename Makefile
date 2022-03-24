# C
CC = gcc
CFLAGS = -g -O2 -std=c11 -pedantic -Wall -Wextra

# C++
CXX = g++
CXXFLAGS = -g -O2 -std=c++17 -pedantic -Wall

all: wordcount wordcount-dynamic libhtab.a libhtab.so

wordcountcc: wordcount-.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

tail: tail.c
	$(CC) $(CFLAGS) $^ -o $@

wordcount:

wordcount-dynamic:

libtab.a:
	ar rcs $@ $^

libtab.so:


clean:
	rm -f *.o *.out *.zip tail wordcount wordcount-dynamic libhtab.a libhtab.so wordcountcc

pack:
	zip xkucha28.zip *.c *.cc *.h Makefile

# C
CC = gcc
CFLAGS = -g -O2 -fPIC -std=c11 -pedantic -Wall -Wextra

# C++
CXX = g++
CXXFLAGS = -g -O2 -std=c++17 -pedantic -Wall

HTAB_OBJS = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o

all: wordcount wordcount-dynamic libhtab.a libhtab.so

wordcountcc: wordcount-.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

tail: tail.c
	$(CC) $(CFLAGS) $^ -o $@

wordcount:

wordcount-dynamic:

libhtab.a: $(HTAB_OBJS)
	ar rcs $@ $^

libhtab.so: $(HTAB_OBJS)
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@

htab_bucket_count.o: htab_bucket_count.c htab.h htab_internal.h
htab_clear.o: htab_clear.c htab.h htab_internal.h
htab_erase.o: htab_erase.c htab.h htab_internal.h
htab_find.o: htab_find.c htab.h htab_internal.h
htab_for_each.o: htab_for_each.c htab.h htab_internal.h
htab_free.o: htab_free.c htab.h htab_internal.h
htab_hash_function.o: htab_hash_function.c
htab_init.o: htab_init.c htab.h htab_internal.h
htab_lookup_add.o: htab_lookup_add.c htab.h htab_internal.h
htab_resize.o: htab_resize.c htab.h htab_internal.h
htab_size.o: htab_size.c htab.h htab_internal.h

clean:
	rm -f *.o *.out *.zip tail wordcount wordcount-dynamic libhtab.a libhtab.so wordcountcc

pack:
	zip xkucha28.zip *.c *.cc *.h Makefile

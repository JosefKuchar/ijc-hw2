# Makefile
# Řešení IJC-DU2, příklad 1,2), 22.3.2022
# Autor: Josef Kuchař, FIT
# Přeloženo: gcc 9.3.0

# C
CC = gcc
CFLAGS_N = -g -O2 -std=c11 -pedantic -Wall -Wextra
CFLAGS = $(CFLAGS_N) -fPIC

# C++
CXX = g++
CXXFLAGS = -g -O2 -std=c++17 -pedantic -Wall

HTAB_OBJS = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o

.PHONY: all run clean pack

all: tail wordcount wordcount-dynamic

wordcountcc: wordcount-.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

tail: tail.c
	$(CC) $(CFLAGS_N) $^ -o $@

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS_N) $^ -o $@

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS_N) $^ -o $@

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
io.o: io.c

run: tail wordcount wordcount-dynamic
	./tail <wordcount.c
	./wordcount <wordcount.c
	export LD_LIBRARY_PATH="." && ./wordcount-dynamic <wordcount.c

clean:
	rm -f *.o *.out *.zip tail wordcount wordcount-dynamic libhtab.a libhtab.so wordcountcc

pack:
	zip xkucha28.zip *.c *.cc *.h Makefile

CC = gcc
CFLAGS = -ggdb -Wall -Werror -std=c11
CFLAGS_TEST = -ggdb -Wall -Werror -std=c11 -lcunit


stackTest: 
	$(CC) $(CFLAGS) src/stack.c src/stack.h testsrc/stacktest.c -o stackTest
	./stackTest 1
	./stackTest 1 2
	rm stackTest

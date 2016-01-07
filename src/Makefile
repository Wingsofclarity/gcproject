TARGET = main
LIBS = -lm
CC = gcc
CFLAGS = -ggdb -Wall -Werror -std=c11 -lcunit
CFLAGS_SPECIAL = -ggdb -Wall -std=c11 -I/usr/local/Cellar/cunit/2.1-3/include /usr/local/Cellar/cunit/2.1-3/lib/libcunit.a

default: $(TARGET) run
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) -MM $(CFLAGS) $*.c > $*.d

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

run:
	./$(TARGET)
test:
	$(TARGET)
	./$(TARGET) < test.txt

gdb:
	gdb ./$(TARGET)

clean:
	-rm -f *~
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -fr *.dSYM
	-rm -f *.gch

clean-win:
	-del *.o
	-del $(TARGET)
	-del *.d
	-del *.h~

heapTest: heap.c heap.h header.c header.h  heap_test.c gc.h gc.c
	@ $(CC) $(CFLAGS_SPECIAL) heap.c heap.h header.c header.h  heap_test.c gc.h gc.c
	@ ./a.out
	@ rm a.out

stackTest:
	@ $(CC) $(CFLAGS) stack.c stack.h -o stackTest
	./stackTest 1
	./stackTest 1 2

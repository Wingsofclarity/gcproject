TARGET = main
LIBS = -lm
CC = gcc
CFLAGS = -ggdb -Wall -Werror -std=c11 -lcunit
CFLAGS_NO_TEST = -ggdb -Wall -Werror -std=c11

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
	rm -f *.o
	rm -f *.d
	rm -f *.gch
	rm -f $(TARGET)
clean-win:
	del *.o
	del $(TARGET)
	del *.d
	del *.h~

hyp:
	@ $(CC) $(CFLAGS_NO_TEST) heap.c header.c heap_test.c heap_traversal.c -o heaptest


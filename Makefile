CC = gcc

part1:
	$(CC) part1.c src/*.c -o part1.o -I headers

.PHONY: clean
clean:
	rm -f *.o
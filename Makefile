CC = gcc

main:
	$(CC) main.c src/*.c -o main.o -I headers

.PHONY: clean
clean:
	rm -f *.o
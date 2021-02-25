CFLAGS = -c -Wall
CC = gcc
LIBS = -lm
all: main
main: thuchanh1.o
	$(CC) thuchanh1.o -o main
thuchanh1.o: thuchanh1.c
	$(CC) $(CFLAGS) thuchanh1.c
clean:
	rm 	-f *.o *-
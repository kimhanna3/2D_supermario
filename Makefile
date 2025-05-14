CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

objects = main.o map.o mario.o util.o enemy.o

game: $(objects)
	$(CC) -o game $(objects) -lncurses

clean:
	rm -f *.o game
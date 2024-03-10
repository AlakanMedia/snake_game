CC = gcc
FLAGS = -lncurses
OBJS = main.o logic.o drawing.o

all: snake_game

snake_game: $(OBJS)
	$(CC) $^ -o $@ $(FLAGS)

main.o: main.c definitions.h
	$(CC) -c main.c $(FLAGS)

logic.o: logic.c definitions.h
	$(CC) -c logic.c $(FLAGS)

drawing.o: drawing.c definitions.h
	$(CC) -c drawing.c $(FLAGS)

clean:
	rm -rf *.o snake_game

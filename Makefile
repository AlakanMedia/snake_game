# Variables
OBJS = main.o logic.o drawing.o

# Creamos el archivo ejecutable de nuestro juego
program: $(OBJS)
	gcc -o snake_game $(OBJS) -lncurses

main.o: main.c definitions.h
	gcc -c main.c -lncurses

logic.o: logic.c definitions.h
	gcc -c logic.c -lncurses

drawing.o: drawing.c definitions.h
	gcc -c drawing.c -lncurses

clean:
	rm -f *.o

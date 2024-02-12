/*
 * Author: Juan Puerta
 * Purpose: Practice my knowledge in C
 */

#include <ncurses.h> // Contiene la librería stdio
#include <stdlib.h> // Contiene la función rand para general números aleatorios
#include <string.h> // Incluye la función memset
#include <time.h>
#include "definitions.h"

int 
main()
{
    unsigned char game_board[NUM_ROWS][NUM_COLUMNS]; // Tablero
    unsigned char option_chosen;

    initscr(); // Inicializa la pantalla
    noecho(); // Deshabilita la impresión de las teclas en la terminal
    srand(time(0)); // Inicializamos el generador de números con una semilla basada en la hora actual 

    do
    {
	clear(); // Limpia la pantalla de la terminal
	draw_banner();

	switch (option_chosen = getch())
	{
	    case '1':
		memset(game_board, ' ', sizeof(game_board));
		start_game(game_board);
		break;
	    case '2':
		clear();
		view_scores();
		break;
	    case '3':
		clear();
		draw_instructions();
		break;;
	}
    }
    while (option_chosen != '4');

    echo(); // Habilita la impresión por terminal
    endwin(); // Restaura el estado original de la terminal

    return 0;
}

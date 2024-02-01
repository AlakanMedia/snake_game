#include <ncurses.h> // Contiene la librería stdio

#define NUM_ROWS 10 // Número de filas de la matriz
#define NUM_COLUMNS 20 // Número de columnas de la matriz

char game_board[NUM_ROWS][NUM_COLUMNS]; // Tablero

void draw_board(char game_board[][NUM_COLUMNS]);

int main()
{
    initscr(); // Inicializa la pantalla
    addstr("Option menu\n1 - Start game\n2 - Exit\n");

    int option_chosen = getch();
    noecho(); // Deshabilita la impresión de las teclas en la terminal

    switch(option_chosen){
        case '1':
            memset(game_board, ' ', sizeof(game_board));
	    draw_board(game_board);
            break;
        case '2':
            addstr("Exiting the game...\n");
            break;
        default:
            addstr("Invalid option\n");
    }


    echo(); // Habilita la impresión por terminal
    endwin(); // Restaura el estado original de la terminal

    return 0;
}

void draw_board(char game_board[][NUM_COLUMNS])
{
    addstr("#--------------------#\n");

    for(int i = 0; i < NUM_ROWS; i++){
	addstr("|");	

	for(int j = 0; j < NUM_COLUMNS; j++)
	    printw("%c", *(*(game_board + i) + j));

	addstr("|\n");	
    }

    addstr("#--------------------#");
}

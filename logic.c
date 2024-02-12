#include <ncurses.h> // Contiene la librería stdio
#include <stdlib.h> // Contiene la función rand para general números aleatorios
#include "definitions.h"

void
start_game(unsigned char game_board[][NUM_COLUMNS])
{
    int segments[(NUM_ROWS * NUM_COLUMNS) - 1][2]; // Arreglo en donde se va a guardar la posición de los segmentos de la serpiente
    int movement[2] = {0, 1}; // [0, 1] derecha, [0, -1] izquierda, [1, 0] abajo, [-1, 0] arriba
    int head[2] = {0, 0}; // Cabeza de la serpiente
    int num_segments = 0; // Número de segmentos actuales que tiene la serpiente; también se puede usar como puntuación
    int apple_drawn = 0; // Para saber si la manzana está dibujada
    unsigned char key_pressed;

    game_board[head[0]][head[1]] = '*';
    nodelay(stdscr, TRUE); // No espera a que el usuario presione una tecla para continuar

    while ((key_pressed = getch()) != '\n')
    {
	clear(); // Limpia la pantalla de la terminal
	change_direction(key_pressed, movement);

	if (game_over(game_board, head[0] + movement[0], 
		      head[1] + movement[1]))
	    break;

	move_snake(game_board, segments, head, movement, 
		   &num_segments, &apple_drawn);

	if (!apple_drawn)
	    draw_apple(game_board, &apple_drawn);

	draw_board(game_board, &num_segments);
	napms(DIFFICULTY); // Añade delay, el tiempo está en milisegundos
	refresh(); // Actualiza la pantalla
    }

    nodelay(stdscr, FALSE); // Espera a que el usuario presione una tecla para continuar
    save_score(&num_segments);
}

void 
change_direction(unsigned char key_pressed, int movement[])
{
    switch (key_pressed)
    {
	case 'k':
	    movement[0] = -1; movement[1] = 0;
	    break;
	case 'j':
	    movement[0] = 1; movement[1] = 0;
	    break;
	case 'h':
	    movement[0] = 0; movement[1] = -1;
	    break;
	case 'l':
	    movement[0] = 0; movement[1] = 1;
	    break;
    }
}

void
move_snake(unsigned char game_board[][NUM_COLUMNS], int segments[][2], 
	   int head[], int movement[], int *num_segments, int *apple_drawn)
{
    if (game_board[head[0] + movement[0]][head[1] + movement[1]] == '@')
    {
	segments[*num_segments][0] = head[0]; 
	segments[*num_segments][1] = head[1];
	(*num_segments)++;
	*apple_drawn = !(*apple_drawn);
    } 
    else
    {
	if ((*num_segments) == 0)
	    game_board[head[0]][head[1]] = ' ';
	else
	    game_board[segments[0][0]][segments[0][1]] = ' ';      
	
	for (int i = 0; i < (*num_segments); i++)
	{
	    if (i < ((*num_segments) - 1))
	    {
		segments[i][0] = segments[i + 1][0];
		segments[i][1] = segments[i + 1][1];
	    }
	    else
	    {
		segments[i][0] = head[0]; 
		segments[i][1] = head[1];
	    }

	    game_board[segments[i][0]][segments[i][1]] = '*';
	}
    }

    head[0] += movement[0]; head[1] += movement[1]; 
    game_board[head[0]][head[1]] = '*';
}

void
draw_apple(unsigned char game_board[][NUM_COLUMNS], int *apple_drawn)
{
    int pos_row, pos_column;

    while (1)
    {
	pos_row = rand() % NUM_ROWS; // Generamos los números aleatorios
	pos_column = rand() % NUM_COLUMNS;

	if (game_board[pos_row][pos_column] != '*')
	{
	    game_board[pos_row][pos_column] = '@';
	    *apple_drawn = !(*apple_drawn);
	    break;
	}
    }
}

int
game_over(unsigned char game_board[][NUM_COLUMNS], int i, int j)
{
    if (i < 0 || i >= NUM_ROWS || j < 0 
	|| j >= NUM_COLUMNS || game_board[i][j] == '*')
	return 1;
    else
	return 0;
}

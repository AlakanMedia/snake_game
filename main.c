#include <ncurses.h> // Contiene la librería stdio
#include <string.h> // Incluye la función memset
#include <stdlib.h> // Contiene la función rand para general números aleatorios
#include <time.h>

#define NUM_ROWS 10 // Número de filas de la matriz
#define NUM_COLUMNS 20 // Número de columnas de la matriz
#define DIFFICULTY 100 // Dificultad del juego

char game_board[NUM_ROWS][NUM_COLUMNS]; // Tablero
int movement[2] = {0, 1}; // [0, 1] derecha, [0, -1] izquierda, [1, 0] abajo, [-1, 0] arriba
int head[2] = {0, 0}; // Cabeza de la serpiente
int segments[(NUM_ROWS * NUM_COLUMNS) - 1][2]; // Arreglo en donde se va a guardar la posición de los segmentos de la serpiente
int num_segments; // Número de segmentos actuales que tiene la serpiente; también se puede usar como puntuación
int apple_drawn; // Para saber si la manzana está dibujada

void start_game(char game_board[][NUM_COLUMNS]);
void draw_board(char game_board[][NUM_COLUMNS]);
void draw_apple(char game_board[][NUM_COLUMNS]);
void move_snake(char game_board[][NUM_COLUMNS]);
void change_direction(char key_pressed, int movement[]);
int game_over(char game_board[][NUM_COLUMNS],int i, int j);

int main()
{
    initscr(); // Inicializa la pantalla
    addstr("Option menu\n1 - Start game\n2 - Exit\n");

    int option_chosen = getch();
    noecho(); // Deshabilita la impresión de las teclas en la terminal

    switch(option_chosen){
        case '1':
            memset(game_board, ' ', sizeof(game_board));
            start_game(game_board);
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

void start_game(char game_board[][NUM_COLUMNS])
{
    char key_pressed;
    game_board[0][0] = '*';

    srand(time(0)); // Inicializamos el generador de números con una semilla basada en la hora actual 
    nodelay(stdscr, TRUE); // No espera a que el usuario presione una tecla para continuar

    while((key_pressed = getch()) != '\n'){
	clear(); // Limpia la pantalla de la terminal
	change_direction(key_pressed, movement);

	if(game_over(game_board, head[0] + movement[0], head[1] + movement[1]))
	    break;

	move_snake(game_board);

	if(!apple_drawn)
	    draw_apple(game_board);

	draw_board(game_board);
	napms(DIFFICULTY); // Añade delay, el tiempo está en milisegundos
	refresh(); // Actualiza la pantalla
    }

    nodelay(stdscr, FALSE); // Espera a que el usuario presione una tecla para continuar
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

void change_direction(char key_pressed, int movement[])
{
    switch(key_pressed){
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

void move_snake(char game_board[][NUM_COLUMNS])
{
    if(game_board[head[0] + movement[0]][head[1] + movement[1]] == '@'){
	segments[num_segments][0] = head[0]; segments[num_segments][1] = head[1];
	num_segments++;
	apple_drawn = !apple_drawn;
    } 
    else{
	game_board[segments[0][0]][segments[0][1]] = ' ';      
	
	for(int i = 0; i < num_segments; i++){
	    if(i < (num_segments - 1)){
		segments[i][0] = segments[i + 1][0];
		segments[i][1] = segments[i + 1][1];
	    }
	    else{
		segments[i][0] = head[0]; 
		segments[i][1] = head[1];
	    }

	    game_board[segments[i][0]][segments[i][1]] = '*';
	}
	
	if(num_segments == 0)
	    game_board[head[0]][head[1]] = ' ';
    }

    head[0] += movement[0]; head[1] += movement[1]; 
    game_board[head[0]][head[1]] = '*';
}

void draw_apple(char game_board[][NUM_COLUMNS])
{
    int pos_row, pos_column;

    while(1){
	pos_row = rand() % NUM_ROWS; // Generamos los números aleatorios
	pos_column = rand() % NUM_COLUMNS;

	if(game_board[pos_row][pos_column] != '*'){
	    game_board[pos_row][pos_column] = '@';
	    apple_drawn = !apple_drawn;
	    break;
	}
    }
}

int game_over(char game_board[][NUM_COLUMNS], int i, int j)
{
    if(i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLUMNS)
	return 1;
    else if(game_board[i][j] == '*')
	return 1;
    else
	return 0;
}

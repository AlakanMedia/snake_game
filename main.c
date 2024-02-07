/*
 * Author: Juan Puerta
 * Purpose: Practice my knowledge in C
 */

#include <ncurses.h> // Contiene la librería stdio
#include <string.h> // Incluye la función memset
#include <stdlib.h> // Contiene la función rand para general números aleatorios
#include <time.h>

#define NUM_ROWS 10 // Número de filas de la matriz
#define NUM_COLUMNS 20 // Número de columnas de la matriz
#define DIFFICULTY 100 // Dificultad del juego
#define FILE_NAME "scores.txt" // Nombre del archivo en donde se guarda la puntuación

void draw_banner();
void draw_instructions();
void save_score(int *score);
void view_scores();
void start_game(char game_board[][NUM_COLUMNS]);
void move_snake(char game_board[][NUM_COLUMNS], int segments[][2], int head[], int movement[], int *num_segments, int *apple_drawn);
void draw_board(char game_board[][NUM_COLUMNS], int *num_segments);
void draw_apple(char game_board[][NUM_COLUMNS], int *apple_drawn);
void change_direction(char key_pressed, int movement[]);
int game_over(char game_board[][NUM_COLUMNS],int i, int j);

int main()
{
    char game_board[NUM_ROWS][NUM_COLUMNS]; // Tablero
    char option_chosen;

    initscr(); // Inicializa la pantalla
    noecho(); // Deshabilita la impresión de las teclas en la terminal
    srand(time(0)); // Inicializamos el generador de números con una semilla basada en la hora actual 

    do{
	clear(); // Limpia la pantalla de la terminal
	draw_banner();

	switch(option_chosen = getch()){
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

    }while(option_chosen != '4');

    echo(); // Habilita la impresión por terminal
    endwin(); // Restaura el estado original de la terminal

    return 0;
}

void draw_banner()
{
    addstr("  _____             _           _____                      \n");
    addstr(" / ____|           | |         / ____|                     \n");
    addstr("| (___  _ __   __ _| | _____  | |  __  __ _ _ __ ___   ___ \n");
    addstr(" \\___ \\| '_ \\ / _` | |/ / _ \\ | | |_ |/ _` | '_ ` _ \\ / _ \\\n");
    addstr(" ____) | | | | (_| |   <  __/ | |__| | (_| | | | | | |  __/\n");
    addstr("|_____/|_| |_|\\__,_|_|\\_\\___|  \\_____|\\__,_|_| |_| |_|\\___|\n");
    
    addstr("\n1 - Start game\n2 - View scores\n3 - Show instrcctions\n4 - Exit\n");
}

void draw_instructions()
{
    addstr("______                           _        _____          _                   _   _\n");
    addstr("|  _  \\                         (_)      |_   _|        | |                 | | (_)\n");
    addstr("| | | |_   _ _ __ ___  _ __ ___  _  ___    | | _ __  ___| |_ _ __ _   _  ___| |_ _  ___  _ __  ___\n");
    addstr("| | | | | | | '_ ` _ \\| '_ ` _ \\| |/ _ \\   | || '_ \\/ __| __| '__| | | |/ __| __| |/ _ \\| '_ \\/ __|\n");
    addstr("| |/ /| |_| | | | | | | | | | | | |  __/  _| || | | \\__ \\ |_| |  | |_| | (__| |_| | (_) | | | \\__ \\\n");
    addstr("|___/  \\__,_|_| |_| |_|_| |_| |_|_|\\___|  \\___/_| |_|___/\\__|_|   \\__,_|\\___|\\__|_|\\___/|_| |_|___/\n\n");

    addstr("h -> Move left\n");
    addstr("l -> Move right\n");
    addstr("j -> Move down\n");
    addstr("k -> Move up\n");
    addstr("return -> Finish the game\n\n");

    addstr("Press any key to close the instructions ");
    getch();
}

void start_game(char game_board[][NUM_COLUMNS])
{
    int segments[(NUM_ROWS * NUM_COLUMNS) - 1][2]; // Arreglo en donde se va a guardar la posición de los segmentos de la serpiente
    int movement[2] = {0, 1}; // [0, 1] derecha, [0, -1] izquierda, [1, 0] abajo, [-1, 0] arriba
    int head[2] = {0, 0}; // Cabeza de la serpiente
    int num_segments = 0; // Número de segmentos actuales que tiene la serpiente; también se puede usar como puntuación
    int apple_drawn = 0; // Para saber si la manzana está dibujada
    char key_pressed;

    game_board[head[0]][head[1]] = '*';

    nodelay(stdscr, TRUE); // No espera a que el usuario presione una tecla para continuar

    while((key_pressed = getch()) != '\n'){
	clear(); // Limpia la pantalla de la terminal
	change_direction(key_pressed, movement);

	if(game_over(game_board, head[0] + movement[0], head[1] + movement[1]))
	    break;

	move_snake(game_board, segments, head, movement, &num_segments, &apple_drawn);

	if(!apple_drawn)
	    draw_apple(game_board, &apple_drawn);

	draw_board(game_board, &num_segments);
	napms(DIFFICULTY); // Añade delay, el tiempo está en milisegundos
	refresh(); // Actualiza la pantalla
    }

    nodelay(stdscr, FALSE); // Espera a que el usuario presione una tecla para continuar

    save_score(&num_segments);
}

void save_score(int *score)
{
    char option_chosen;
    addstr("Do you want save your score [Y/n] ");

START:
    option_chosen = getch();

    if(option_chosen != 'Y' && option_chosen != 'y' && option_chosen != 'N' && option_chosen != 'n') 
	goto START;

    if(option_chosen == 'y' || option_chosen == 'Y'){
	FILE *score_file = fopen(FILE_NAME, "a");

	if(score_file == NULL){
	    addstr("File could not be opened\nPress any key to exit ");
	    getch();
	}
	else{
	    char character;
	    char *nickname;
	    char *line_save;
		
	    addstr("\nEnter your nickname: ");

	    int i;

	    for(i = 0; (character = getch()) != '\n'; i++)
		*(nickname + i) = character;
	    *(nickname + i) = '\0';

	    fprintf(score_file, "%s -> %d\n", nickname, *score);

	    addstr("\nScore saved correctly\nPress any key to exit ");
	    getch();
	}

	fclose(score_file);
    }
}

void view_scores()
{
    FILE *score_file = fopen(FILE_NAME, "r");

    if(score_file == NULL){
        addstr("File could not be opened\nPress any key to exit ");
        getch();
    }
    else{
	char max_length = 100;
	char bufer[max_length];

	addstr("Scores\n\n");

	while(fgets(bufer, max_length, score_file))
	    printw("%s", bufer);

	addstr("\nPress any key to exit ");
	getch();
    }

    fclose(score_file);
}

void draw_board(char game_board[][NUM_COLUMNS], int *num_segments)
{
    addstr("                  oo\n");
    addstr("   . . . __/\\_/\\_/`'\n");
    addstr("+--------------------+\n");

    for(int i = 0; i < NUM_ROWS; i++){
	addstr("|");	

	for(int j = 0; j < NUM_COLUMNS; j++)
	    printw("%c", *(*(game_board + i) + j));

	addstr("|\n");	
    }

    addstr("+--------------------+\n");
    printw("|Score: %13d|\n", *num_segments);
    addstr("+--------------------+");
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

void move_snake(char game_board[][NUM_COLUMNS], int segments[][2], int head[], int movement[], int *num_segments, int *apple_drawn)
{
    if(game_board[head[0] + movement[0]][head[1] + movement[1]] == '@'){
	segments[*num_segments][0] = head[0]; segments[*num_segments][1] = head[1];
	(*num_segments)++;
	*apple_drawn = !(*apple_drawn);
    } 
    else{
	if((*num_segments) == 0)
	    game_board[head[0]][head[1]] = ' ';
	else
	    game_board[segments[0][0]][segments[0][1]] = ' ';      
	
	for(int i = 0; i < (*num_segments); i++){
	    if(i < ((*num_segments) - 1)){
		segments[i][0] = segments[i + 1][0];
		segments[i][1] = segments[i + 1][1];
	    }
	    else{
		segments[i][0] = head[0]; 
		segments[i][1] = head[1];
	    }

	    game_board[segments[i][0]][segments[i][1]] = '*';
	}
    }

    head[0] += movement[0]; head[1] += movement[1]; 
    game_board[head[0]][head[1]] = '*';
}

void draw_apple(char game_board[][NUM_COLUMNS], int *apple_drawn)
{
    int pos_row, pos_column;

    while(1){
	pos_row = rand() % NUM_ROWS; // Generamos los números aleatorios
	pos_column = rand() % NUM_COLUMNS;

	if(game_board[pos_row][pos_column] != '*'){
	    game_board[pos_row][pos_column] = '@';
	    *apple_drawn = !(*apple_drawn);
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

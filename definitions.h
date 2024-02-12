#ifndef DEFINITIONS
#define	DEFINITIONS 

#define NUM_ROWS 10		// Número de filas de la matriz
#define NUM_COLUMNS 20		// Número de columnas de la matriz
#define DIFFICULTY 100		// Dificultad del juego
#define FILE_NAME "scores.txt"	// Nombre del archivo en donde se guarda la puntuación

// Prototypes of the functions controlling the program logic 
void start_game(unsigned char game_board[][NUM_COLUMNS]);
void change_direction(unsigned char key_pressed, int movement[]);
int game_over(unsigned char game_board[][NUM_COLUMNS],int i, int j);
void draw_apple(unsigned char game_board[][NUM_COLUMNS], int *apple_drawn);
void move_snake(unsigned char game_board[][NUM_COLUMNS], int segments[][2], 
		int head[], int movement[], int *num_segments, 
		int *apple_drawn);

// Prototypes of the functions that are responsible for displaying text in the terminal
void draw_banner();
void view_scores();
void draw_instructions();
void save_score(int *score);
void draw_board(unsigned char game_board[][NUM_COLUMNS], int *num_segments);

#endif // DEFINITONS

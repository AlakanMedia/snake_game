#include <ncurses.h> // Contiene la librería stdio

#include "definitions.h"

void draw_banner()
{
    addstr("THE SNAKE GAME\n\n");

    addstr("1 - Start game\n2 - View scores\n3 - Show instructions\n4 - Exit\n");
}

void draw_instructions()
{
    addstr("DUMMIE INSTRUCTIONS\n\n");

    addstr("h -> Move left\n");
    addstr("l -> Move right\n");
    addstr("j -> Move down\n");
    addstr("k -> Move up\n");
    addstr("return -> Finish the game\n\n");

    addstr("Press any key to close the instructions ");
    getch();
}


void save_score(int *score)
{
    char option_chosen;
    addstr("Do you want save your score? [Y/n] ");

START:
    option_chosen = getch();

    if(option_chosen != 'Y' && option_chosen != 'y' && option_chosen != 'N' && option_chosen != 'n') 
	goto START;

    if(option_chosen == 'y' || option_chosen == 'Y'){
	FILE *score_file = fopen(FILE_NAME, "a");

	if(score_file == NULL)
	    addstr("File could not be opened");
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

	    addstr("\n\nScore saved correctly");
	}

	fclose(score_file);

	addstr("\nPress any key to exit ");
	getch();
    }
}

void view_scores()
{
    FILE *score_file;

    if(score_file = fopen(FILE_NAME, "r")){
	char max_length = 100;
	char bufer[max_length];

	addstr("SCORES\n\n");

	while(fgets(bufer, max_length, score_file))
	    printw("%s", bufer);

	fclose(score_file);
    }
    else
        addstr("The \"scores.txt\" file doesn't exits\nPlay to create the file"); 

    addstr("\n\nPress any key to exit ");
    getch();
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

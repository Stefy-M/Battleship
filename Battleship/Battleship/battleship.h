#ifndef battleship_h
#define battleship_h
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct coordinate{
	int row;
	int column;

}Coordinate;

typedef struct cell{
	int occupied;
	char symbol;
	Coordinate location;

}Cell;

typedef struct stats{
	int num_hits;
	int num_misses;
	int total_shots;
	int hit_miss_ratio;

}Stats;

typedef struct ships{
	char symbol;
	int length;
	char *name;


}Ships;



void welcome_screen();
void output_current_move(FILE*outfile, char const *player, Stats s);
Cell **initialize_game_board(int size);
void print_board(int player,Cell **board,int size, char show_ships);
void manually_place_ships(Cell **playerboard,char carrier [],char battleship []
,char cruiser [],char submarine [], char destroyer []);
void automatically_place_ships(Cell **playerboard,Ships s[]);
Coordinate get_position(int direction,int length);
void place_ship(Cell **board,Ships s,Coordinate position,int direction);
int is_winner(Stats s [], int player);
Coordinate target (void);
void update_board(Cell **board, Coordinate target);
int check_shot(Cell **board,Coordinate target);
int isValid(Cell **board, Coordinate position, int direction, int length);



#endif
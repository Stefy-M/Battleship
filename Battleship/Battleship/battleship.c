#include "battleship.h";
void welcome_screen(){
	printf("    *****Welcome to BattleShip*****\n\n\n");
	printf("         Rules of Game.\n");
	printf("_________________________________________________________\n");
	printf("1. This is a two player game\n");
	printf("2. You are Player 1, Player 2 is a Computer\n");
	printf("3. Place ships manually or automatically Player 2s ships are automatically placed\n");
	printf("4. Enter coordiantes of area you would like to hit\n");
	printf("5. The indication for a hit is '*' if you missed any ships the coordinate will be marked with an 'm'\n");
	printf("6. Player 2 coordinates will be automatically placed\n");
	printf("7. Which ever Player sinks all ships first WINS\n\n\n");




}
Cell **initialize_game_board(int size){
	Cell **board =0;
	int i,j,p;

	
	board = (Cell **)malloc(sizeof(Cell *)*size);
	for (p =0; p<size;p++){
		board[p] = (Cell*)malloc(sizeof(Cell)*size);
	}

	for(i =0; i<size;i++){
		for(j =0; j<size;j++){
			board[i][j].symbol ='~';
			board[i][j].occupied =0;
			board[i][j].location.row=i;
			board[i][j].location.column=j;

		}
	}
	return board;

}
void print_board(int player,Cell **board,int size, char show_ships){
	int i,j;
	char h = '*';
	char m = 'm';
	char w = '~';
	printf("Player %d's Board\n\n",player);
	printf(" 0	1	2	3	4	5	6	7	8	9\n");
	//Rows
	for ( i =1; i<size;i++){
		printf("\n%d ",i);

		// columns
		for ( j =0; j<size;j++){
			if (show_ships == 'y'){
			printf("%c\t ", board[i][j].symbol);
			}
			else{
				if(board[i][j].symbol=='*'){
					printf("%c\t",h);
				}
				else if (board[i][j].symbol=='m'){
					printf("%c\t",m);
				}
				else{
					printf("%c\t",w);
				}
			}


		}
	}
	printf("\n");

}
void manually_place_ships(Cell **playerboard,char carrier [],char battleship []
,char cruiser [],char submarine [], char destroyer []){
	int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5;
	
	// Place carrier
	printf("Please enter the five cells to place the carrier ship across: ");
	scanf("%d %d %d %d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4,&x5,&y5);
	playerboard[x1][y1].symbol = carrier[0];
	playerboard[x2][y2].symbol = carrier[1];
	playerboard[x3][y3].symbol = carrier[2];
	playerboard[x4][y4].symbol = carrier[3];
	playerboard[x5][y5].symbol = carrier[4];
	// Place battleship
	printf("Please enter the four cells to place the battle ship: ");
	scanf("%d %d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
	playerboard[x1][y1].symbol = battleship[0];
	playerboard[x2][y2].symbol = battleship[1];
	playerboard[x3][y3].symbol = battleship[2];
	playerboard[x4][y4].symbol = battleship[3];
	// Place crusier
	printf("Please enter the three cells to place the crusier ship: ");
	scanf("%d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3);
	playerboard[x1][y1].symbol = cruiser[0];
	playerboard[x2][y2].symbol = cruiser[1];
	playerboard[x3][y3].symbol = cruiser[2];
	// Place submarine
	printf("Please enter the two cells to place the submarine ship: ");
	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	playerboard[x1][y1].symbol = submarine[0];
	playerboard[x2][y2].symbol = submarine[1];
	// Place destroyer
	printf("Please enter the cells to place the destroyer ship: ");
	scanf("%d %d",&x1,&y1);
	playerboard[x1][y1].symbol = destroyer[0];
	

	
	

}
void automatically_place_ships(Cell **playerboard,Ships s[]){
	Coordinate place;
	int direction =-1,i=0,Valid =1;
	for(i =0; i<5;i++){
		while(Valid){
			direction = rand()%1;// 0 = horizontal, 1 = vertical
			place = get_position(direction,s[i].length);
			if(isValid(playerboard,place,direction,s[i].length)==1){// checks to see if coordinate isnt already filled
			break;
			}
		}
		place_ship(playerboard,s[i],place,direction);
		

	}
	

}
	


int is_winner(Stats s [], int player){
	int win = 0;

	if (s[player].num_hits == 15){
		win = 1;

	}


	return win;


}
Coordinate target (void){
	Coordinate target;

	printf("Enter row and column to hit: ");
	scanf("%d %d",&target.row,&target.column);

	return target;

}
void update_board(Cell **board, Coordinate target){
	switch(board[target.row][target.column].symbol){//

	case '~':
		board[target.row][target.column].symbol = 'm';
		break;
	case 'c':
	case 'b':
	case 'r':
	case 's':
	case 'd':
		board[target.row][target.column].symbol = '*';
		break;
	case '*':
	case 'm':
	default:
		break;
	}


}
int check_shot(Cell **board,Coordinate target){
	int hit = -2;

	switch(board[target.row][target.column].symbol){

	case '~':
		hit =0;
		break;
	case 'c':
	case 'b':
	case 'r':
	case 's':
	case 'd':
		hit = 1;
		break;
	case '*':
	case 'm':
	default:
		hit = -1;
		break;
	}
	return hit;

}
Coordinate get_position(int direction,int length){
	Coordinate position;
	int t = 9-length;
	// if direction is going to left or right 
	if(direction ==0){
		// random row 1-9
		position.row = rand()%9;
		// random column 1-length of ship
		position.column = rand()%t;

	}
	//if direction is going up or down
	else{

		position.row = rand()%t;
		position.column = rand()%9;

	}
	return position;
}
void place_ship(Cell **board,Ships s,Coordinate position,int direction){
	int i;

	for (i =0; i <s.length; i++){
		if (direction ==0){ 
			board[position.row][position.column+i].symbol=s.symbol;
		}else{
			board[position.row+1][position.column].symbol=s.symbol;

		}

	}



}
int isValid(Cell **board, Coordinate position, int direction, int length){
	int i = length -1;
	int valid =1;
	for(i =0; valid ==1 && i <length;i++){
		if (direction ==0){// If direction is horizontal

			if(board[position.row][position.column+i].symbol != '~' && (position.column+i)<10){
				valid=0;
			}

		}else{
			if (board[position.row+i][position.column].symbol !='~' && (position.row+i)<10){
				valid =0;
			}

		}
		return valid;
	}


}
/*
Stefon Martin
11/17/15
Assignment: Battleship
Contributions: Lab Task 10

*/




#include "battleship.h";

int main(void){
	// Initiate variables
	Stats s [2];
	Cell**player1board;
	Cell **player2board;
	Coordinate selected;
	Coordinate t;
	Ships ships[5] ={{'c',5,"Carrier"},{'b',4,"Battleship"},{'r',3,"Crusier"},{'s',2,"Submarine"},{'d',1,"Destroyer"}};
	char carrier [5] = {'c','c','c','c','c'};
	char battleship [4] ={'b','b','b','b'};
	char crusier [3] = {'r','r','r'};
	char submarine [2] ={'s','s'};
	char destroyer [1] ={'d'};
	char hit = '*';
	char miss = 'm';
	char symbol ='\0';
	int menu_option=0, player=0,shot=0;


	//open file for battleship stats to transfer
	FILE*outfile= NULL;
	outfile = fopen("battleship.txt","w");
	

	srand(time(NULL));

	// Zero out all of stats
	s[0].num_hits =s[0].num_misses = s[0].hit_miss_ratio =s[0].total_shots =0;
	s[1].num_hits =s[1].num_misses = s[1].hit_miss_ratio =s[1].total_shots =0;



	//Welcom Screen
	welcome_screen();
	system("pause");
	system("cls");
	//Menu for User
	printf("Please select from the following menu\n");
	printf("1. Enter postions of ships manually\n");
	printf("2. Allow program to randomly select postions of ships\n");

	//Scan option from user
	scanf("%d",&menu_option);

	//Initialize boards
	player1board = initialize_game_board(10);
	player2board = initialize_game_board(10);
	
	// Switch case from user

	switch(menu_option){
	case 1:// If user enters 1 from menu
		manually_place_ships(player1board,carrier, battleship ,crusier ,submarine, destroyer);


			break;

	case 2:// If user enters 2 from menu
		automatically_place_ships(player1board,ships);
		
		

			break;
	}
	// After user (Player 1) places ships manually or automatically
			automatically_place_ships(player2board,ships);
			printf("Player 2's ships have been placed...\n\n\n\n");
			system("pause");

			// Randomize which user goes first nums 0-1
			player = rand ()%2;

			//Prints which player is going first
			printf("Player %d has randomly been selected to play first\n\n\n\n", player+1);
			system("pause");
			system("cls");
			
			//Loop keeps going until a player has a total of 15 hits
			while(is_winner(s,player)==0){
				//Print which player turn it is into outfile after each loop
				fprintf(outfile,"Player %d's turn\n\n",player +1);


				switch(player){
					// if player 1 was randomized to go first
				case 0:
					printf("Player 1's Turn\n\n");
					print_board(2 ,player2board,10,'n'); // Print player 2's board and dont show ships

					do{ // Loop will repeat if user enters a coordinate that has already been entered
						t = target(); // Get coordinate from user
						shot = check_shot(player2board,t); // Checks to see if shot is a hit or miss
						
						
						
						if (shot ==-1){ 
							printf("Target already been used. TRY AGAIN\n\n");
							

						}




					}while(shot ==-1);

					symbol =player2board[t.row][t.column].symbol;
					break;
					
					

				case 1:// Computers turn
					printf("Computers Turn\n\n ");
					print_board(1,player1board,10,'y'); // Show Player 1's Board with ships shown
					do{// Computer randomly chooses coordinates. Not a very good AI 
						t.row = rand()%9;
						t.column = rand()%9;

						shot = check_shot(player1board,t);
						


					}while(shot ==-1);

					break;
				}

				if(shot ==1){ // Hit
					//Find coordinate that was a hit
						printf("Target: %d %d was a HIT!\n\n",t.row,t.column); 
						s[player].num_hits++; // Counts the hit to stats
						fprintf(outfile,"Target: %d %d was a HIT!\n\n",t.row,t.column); // prints to outfile

					}
				else if(shot ==0){//MISS
						
					//Find coordinate that was a miss
						printf("Target: %d %d was a MISS!\n\n",t.row,t.column);
						s[player].num_misses++; // Counts the miss to stats
						fprintf(outfile,"Target: %d %d was a MISS!\n\n",t.row,t.column); // prints to outfile


					}
				if(player ==0){//Updated board after hit or miss
					update_board(player2board,t);

				}else{

					update_board(player1board,t);
				}
				if(is_winner(s,player)==1){// If any player has 15 hits they win the game
					printf(" -----------------------\n");
					printf(" |  PLAYER %d WINS!!!!  |\n",player+1);
					printf(" -----------------------\n\n");

				
					fprintf(outfile," -----------------------\n");
					fprintf(outfile," |  PLAYER %d WINS!!!!  |\n",player+1);
					fprintf(outfile," -----------------------\n\n");
					break;

				}
				system("pause");
				player = !player; // This helps the switch case switch through cases(players) until while loop is finished
				system("cls");
				
				
}
			s[0].total_shots = s[0].num_hits+s[0].num_misses;// Calculate hits from player 1
			s[1].total_shots = s[1].num_hits+s[1].num_misses;// Calculates misses from player 2
			
			//Pint all stats to outfile after game is over
			fprintf(outfile,"Player 1 Num of Hits: %d\n",s[0].num_hits);
			fprintf(outfile,"Player 1 Num of Misses: %d\n",s[0].num_misses);
			fprintf(outfile,"Player 1 Total Shots: %d\n",s[0].total_shots);
			fprintf(outfile,"Player 1 Hit Miss Ratio: %d:%d\n",s[0].num_hits,s[0].num_misses);
			fprintf(outfile,"-------------------------------------------\n\n\n");
			fprintf(outfile,"Player 2 Num of Hits: %d\n",s[1].num_hits);
			fprintf(outfile,"Player 2 Num of Misses: %d\n",s[1].num_misses);
			fprintf(outfile,"Player 2 Total Shots: %d\n",s[1].total_shots);
			fprintf(outfile,"Player 2 Hit Miss Ratio: %d:%d\n",s[1].num_hits,s[1].num_misses);

				fclose(outfile);
}
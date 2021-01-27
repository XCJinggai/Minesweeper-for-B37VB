/*
* File name: main.c
* Author: Fengxi Zhang & Chengchu Wu
* HW ID: H00365040 & H00365059
* IDE: Visual Studio 2017 Community
* Description: Define main function and game function.
* Date: 15/1/2021
*/

/* Include file game.h */
#include "game.h"

/*
* Function name: game function
* Description:  Include other functions to execute the game program.
*/
void game(void)
{
	double  start, finish;
	int ret = 0;

	init_mine();/* Initialize two char arrays named show_mine and real_mine */
	set_mine(); /* Set up mines for real_time array */
	/* Print checkerboard contains real_time array for designer(CAN be delete.Just for testing the program)

	print_mine();

	*/
	printf("\n");
	print_player(); /* Print checkerboard of show_mine array for player */
	start = clock(); /* Get start time */
	safe_mine(); /* Prevent player from being blown up for the first time */

	if (count_show_mine() == COUNT) /* The situation that one step to win */
	{
		print_mine();
		printf("YOU WIN£¡\n\n");
		return;
	}
	print_player();    /* Print checkerboard of show_mine array for player */

	while (1)  /* Loop sweeping */
	{
		int ret = sweep_mine();/* Sweep the mine. Return 1 if player's input is on a mine;return 0 if player's is not on a mine. */

		if (count_show_mine() == COUNT)/* If the number of '*' on the player's checkerboard is the number of mines.YOU WIN! */
		{
			print_mine();  /*Print checkerboard contains real_mine array for player to view the distribution of mines */
			printf("YOU WIN£¡\n\n");
			finish = clock(); /* Get finish time */
			printf("You have spent %d seconds\n", (int)(finish - start) / CLOCKS_PER_SEC);
			break;
		}

		if (ret) /* Judge if player's input is on a mine */
		{
			printf("GAME OVER! YOU WERE BLOWN UP!\n");
			finish = clock(); /* Get finish time */
			printf("You have spent %d seconds\n", (int)(finish - start) / CLOCKS_PER_SEC);
			print_mine(); /*Print checkerboard contains real_mine array for player to view the distribution of mines */
			break;
		}

		print_player(); /* Print checkerboard contains show_mine array for player */
	}
}

/*
* Function name: main function
* Description:  Input 1 to begin the game. Input 0 to quit the game.
*               Do not allow to input others.
*/
int main(void)
{
	srand((unsigned int)time(NULL));  /* Generate random number seeds */

	int input = 0;

	menu(); /* Print the beginning menu */

	do
	{
		scanf_s("%d", &input); /* assign player's input to the variable "input" */
		switch (input)
		{
		case 1:
			game(); /* execute the game function to begin the game */
			break;
		case 0:
			exit(0); /* quit the game */
			break;
		default:
			printf("Your input is ILLEGAL,please RETYPE!\n");
			break;
		}
		menu();
		printf("contiue?\n");
	} while (input); /* Create a loop through which player can replay the game after a game over */

	return 0;
}
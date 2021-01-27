/*
* File name: game.c
* Author: Fengxi Zhang & Chengchu Wu
* HW ID: H00365040 & H00365059
* IDE: Visual Studio 2017 Community
* Description: Define menu, init_mine, print_player, print_mine, set_mine, count_mine, safe_mine,
*			   sweep_mine, open_mine, count_show_mine functions.
* Date: 14/1/2021
*/

/* Include file game.h */
#include "game.h"

/* Initialize arrays */
char show_mine[ROWS][COLS] = { 0 };
char real_mine[ROWS][COLS] = { 0 };

/*
* Function name: menu
* Description: Print game beginning menu
*/
void menu(void)
{
	printf("***************************************\n");
	printf("*****   Enter 1 or 0 to continue! *****\n");
	printf("*********1.play       0.exit***********\n");
	printf("***************************************\n");
}

/*
* Function name: init_mine
* Description: Initialize two arrays.
*/
void init_mine(void)
{
	int i = 0;
	int j = 0;

	for (int i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			show_mine[i][j] = '*';
			real_mine[i][j] = '0';
		}
	}
}

/*
* Function name: print_player
* Description: Print checkerboard contains show_mine array for player.
*/
void print_player(void)
{
	int i = 0;
	int j = 0;
	printf("0  ");

	for (i = 1; i < ROWS - 1; i++)
	{
		printf("%d ", i); /* Print the horizontal coordinates£¨0--10£©*/
	}
	printf("\n");

	for (i = 1; i < ROWS - 2; i++) /* Print the vertical coordinates £¨1--10£©*/
	{
		printf("%d  ", i);
		for (j = 1; j < COLS - 1; j++)
		{
			printf("%c ", show_mine[i][j]);
		}
		printf("\n");
	}
	printf("10 "); /* Print the last line */

	for (i = 1; i < ROWS - 1; i++)
	{
		printf("%c ", show_mine[10][i]);
	}
	printf("\n");
}

/*
* Function name: print_mine
* Description: Print the checkerboard contains real_mine array for player to look at the answer.
*/
void print_mine(void)
{
	int i = 0;
	int j = 0;
	printf("0  ");

	for (i = 1; i < ROWS - 1; i++)
	{
		printf("%d ", i); /* Print the horizontal coordinates£¨0--10£©*/
	}
	printf("\n");

	for (i = 1; i < ROWS - 2; i++) /* Print the vertical coordinates£¨1--10£©*/
	{
		printf("%d  ", i);
		for (j = 1; j < COLS - 1; j++)
		{
			printf("%c ", real_mine[i][j]);
		}
		printf("\n");
	}
	printf("10 "); /* Print the last line */

	for (i = 1; i < ROWS - 1; i++)
	{
		printf("%c ", real_mine[10][i]);
	}
	printf("\n");
}

/*
* Function name: set_mine
* Description: Set mines for real_mine array. 1 represents there is a mine. 0 represents there is no mine.
*/
void set_mine(void)
{
	int x = 0;
	int y = 0;
	int count = COUNT; /* The number of mines */

	while (count) /* Break the loop when mines are set up */
	{
		int x = rand() % 10 + 1; /* Generates a random number from 1 to 10,setting up a mine at a horizontal coordinate from 1 to 10 */
		int y = rand() % 10 + 1;
		if (real_mine[x][y] == '0') /* Find a place where is no mine to set up a mine. */
		{
			real_mine[x][y] = '1';
			count--;
		}
	}
}

/*
* Function name: count_mine
* Description: Detect the number of mines in the surrounding 8 areas of the coordinate player input.
*/
int count_mine(int x, int y)
{
	int count = 0;
	if (real_mine[x - 1][y - 1] == '1')
		count++;
	if (real_mine[x - 1][y] == '1')
		count++;
	if (real_mine[x - 1][y + 1] == '1')
		count++;
	if (real_mine[x][y - 1] == '1')
		count++;
	if (real_mine[x][y + 1] == '1')
		count++;
	if (real_mine[x + 1][y - 1] == '1')
		count++;
	if (real_mine[x + 1][y] == '1')
		count++;
	if (real_mine[x + 1][y + 1] == '1')
		count++;
	return count;
}

/*
* Function name: safe_mine
* Description: Prevent player from being blown up for the first time he/she input.
*/
void safe_mine(void)
{
	int x = 0;
	int y = 0;
	char ch = 0;
	int count = 0;
	int ret = 1;
	printf("Enter coordinate:x(column) y(row) to sweep mine.\n");
	printf("Beware: There is a SPACE between x and y that you input!\n");

	while (1)
	{
		scanf_s("%d %d", &y, &x);
		if ((x >= 1 && x <= 10) && (y >= 1 && y <= 10))/* Determine if the input coordinate is form 1 to 10, enter again if the input is wrong */
		{
			if (real_mine[x][y] == '1') /* Remedy if the first input is on a mine. */
			{
				real_mine[x][y] = '0';
				char ch = count_mine(x, y);
				show_mine[x][y] = ch + '0'; /* The difference between the ASCII value of a digit and the ASCII value of a numeric character is 48, which is the ASCII value of '0' */
				open_mine(x, y);
				while (ret) /* Set up a mine in the remaining free space */
				{
					int x = rand() % 10 + 1; /* Generates a random number from 1 to 10,setting up a mine at a horizontal coordinate from 1 to 10 */
					int y = rand() % 10 + 1;
					if (real_mine[x][y] == '0') /* Find a place where is no mine to set up a mine. */
					{
						real_mine[x][y] = '1';
						ret--;
						break;
					}
				}
				break; /* Break the function */
			}
			if (real_mine[x][y] == '0')
			{
				char ch = count_mine(x, y);
				show_mine[x][y] = ch + '0'; /* The difference between the ASCII value of a digit and the ASCII value of a numeric character is 48, which is the ASCII value of '0' */
				open_mine(x, y);
				break;
			}
		}
		else /* The coordinate is wrong */
		{
			printf("Your input is wrong!Please RETYPE!\n");
		}
	}
}

/*
* Function name: sweep_mine
* Description: Sweep the mine. Return 1 if player's input is on a mine, 0 if player's input isn't on a mine.
*/
int sweep_mine(void)
{
	int x = 0;
	int y = 0;
	int count = 0;
	printf("Enter coordinate:x(column) y(row) to sweep mine.\n");
	printf("Beware: There is a SPACE between x and y that you input!\n");
	scanf_s("%d %d", &y, &x);

	if ((x >= 1 && x <= 10) && (y >= 1 && y <= 10))/* Determine if the input coordinate is form 1 to 10, enter again if the input is wrong */
	{
		if (real_mine[x][y] == '0') /* Player's input is not on a mine */
		{
			char ch = count_mine(x, y);
			show_mine[x][y] = ch + '0'; /* The difference between the ASCII value of a digit and the ASCII value of a numeric character is 48, which is the ASCII value of '0' */
			open_mine(x, y);
			if (count_show_mine() == COUNT) /* Determine the number of unknown areas left. If the number is the number of mines, then the player win. */
			{
				print_mine();
				printf("You WIN£¡\n\n");
				return 0;
			}
		}
		else if (real_mine[x][y] == '1') /* Met the mine */
		{
			return 1;
		}

	}
	else
	{
		printf("Your input is wrong!Please RETYPE!\n");
	}
	return 0; /* Player's input is not on a mine */
}

/*
* Function name: open_mine
* Description: Expand coordinate's surroundings.
*/
void open_mine(int x, int y)
{
	if (real_mine[x - 1][y - 1] == '0')
	{
		show_mine[x - 1][y - 1] = count_mine(x - 1, y - 1) + '0';/* Displays the number of mines around this coordinate */
	}
	if (real_mine[x - 1][y] == '0')
	{
		show_mine[x - 1][y] = count_mine(x - 1, y) + '0';
	}
	if (real_mine[x - 1][y + 1] == '0')
	{
		show_mine[x - 1][y + 1] = count_mine(x - 1, y + 1) + '0';
	}
	if (real_mine[x][y - 1] == '0')
	{
		show_mine[x][y - 1] = count_mine(x, y - 1) + '0';
	}
	if (real_mine[x][y + 1] == '0')
	{
		show_mine[x][y + 1] = count_mine(x, y + 1) + '0';
	}
	if (real_mine[x + 1][y - 1] == '0')
	{
		show_mine[x + 1][y - 1] = count_mine(x + 1, y - 1) + '0';
	}
	if (real_mine[x + 1][y] == '0')
	{
		show_mine[x + 1][y] = count_mine(x + 1, y) + '0';
	}
	if (real_mine[x + 1][y + 1] == '0')
	{
		show_mine[x + 1][y + 1] = count_mine(x + 1, y + 1) + '0';
	}
}

/*
* Function name: count_show_mine function
* Description: Count the number of '*' left on the checkerboard contains show_mine.
*/
int count_show_mine()
{
	int i = 0;
	int j = 0;
	int count = 0;
	for (i = 1; i <= ROWS - 2; i++)
	{
		for (j = 1; j <= COLS - 2; j++)
		{
			if (show_mine[i][j] == '*')
			{
				count++;
			}
		}

	}
	return count;
}
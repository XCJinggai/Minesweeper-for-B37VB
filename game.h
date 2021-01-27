/*
* File name: game.h
* Author: Fengxi Zhang & Chengchu Wu
* HW ID: H00365040 & H00365059
* IDE: Visual Studio 2017 Community
* Description: Include header files. Define object-like macros.
*              State arrays. State functions.
* Date: 15/1/2021
*/

#ifndef _GAME_H_
#define _GAME_H_

/* Include header files */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* Define object-like macros */
#define ROW 10 /* The number of checkerboard's rows */
#define COL 10 /* The number of checkerboard's columns */
#define COUNT 10   /* The number of mines */

#define ROWS (ROW+2)  /* The number of arrays' rows */
#define COLS (COL+2)  /* The number of arrays' columns */

/* State arrays */
extern char show_mine[ROWS][COLS];  /* State an array for show */
extern char real_mine[ROWS][COLS];  /* State an array for setting mines */

/* State functions */
void menu(void);
void init_mine(void);
void set_mine(void);
int  count_mine(int x, int y);
void print_player(void);
void print_mine(void);
int  sweep_mine(void);
void safe_mine(void);
void open_mine(int x, int y);
int count_show_mine(void);

#endif  /* _GAME_H_ */

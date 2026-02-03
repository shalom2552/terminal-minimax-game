#include "game_display.h"
#include "game_input.h"
#include "game_logic.h" // Game
#include "game_menu.h"	// MenuItems

#include <stdio.h>  // printf
#include <stdlib.h>
#include <unistd.h>

/* colors to display board */
#define COLOR_WHITE_RESET		"\033[0m"
#define COLOR_GREEN_HUMAN		"\033[32m"
#define COLOR_RED_AI			"\033[31m"
#define COLOR_ORANGE_ACTIVE		"\033[33m"
#define COLOR_BG_BLUE_CURSOR	"\033[44m"
#define COLOR_BOLD				"\033[1m"
#define COLOR_BG_GREEN			"\033[48;5;22m"
#define COLOR_BG_RED			"\033[48;5;88m"
#define COLOR_CYAN_BOX				"\033[36m"

/* ansi values to draw the board */
#define BOARD_WIDTH 39
#define ANSI_BOX_HOR		"\u2500" // ─
#define ANSI_BOX_VER		"\u2502" // │
#define ANSI_BOX_TL			"\u250C" // ┌
#define ANSI_BOX_TR			"\u2510" // ┐
#define ANSI_BOX_BL			"\u2514" // └
#define ANSI_BOX_BR			"\u2518" // ┘
#define ANSI_BOX_CROSS		"\u253C" // ┼
#define ANSI_BOX_T_TOP		"\u252C" // ┬
#define ANSI_BOX_T_BOT		"\u2534" // ┴
#define ANSI_BOX_T_L		"\u251C" // ├
#define ANSI_BOX_T_R		"\u2524" // ┤

/* ansi values to draw the score box */
#define BOX_WIDTH 33
#define ANSI_FRAME_TL  "\u2554" // ╔
#define ANSI_FRAME_TR  "\u2557" // ╗
#define ANSI_FRAME_BL  "\u255a" // ╚
#define ANSI_FRAME_BR  "\u255d" // ╝
#define ANSI_FRAME_H   "\u2550" // ═
#define ANSI_FRAME_V   "\u2551" // ║

#define ANSI_CLEAR "\033[H\033[2J\033[3J"

/* Prints the game board to the screen */
static void display_grid(Game const* state, int cursor_row, int cursor_col);

/* print cell acording to collors */
static void ansi_print_cell(Game const* state, int row, int col, int cursor_row, int cursor_col);

/* print players state and current turn */
static void display_score(Game const* state);

/* print the top line of the board */
static void ansi_print_top_line(void);

/* print the middle line of the board */
static void ansi_print_mid_line(void);

/* print the bottom line of the board */
static void ansi_print_bot_line(void);

/* get the right color for the sell accordind to game state */
static char* ansi_get_color(Game const* state, int row, int col);

/* display whous turn it is */
static void display_turn(Game const* state);

/* display the end resuts of the game win, draw lose */
static void display_results(Game const* state);

/* Print big 'GAME OVER' text on the screen */
static void ansi_print_game_over(void);

/* Print big 'MINIMAX' text on the screen */
static void ansi_print_minimax(void);

/* Print to the user how to play and controls */
static void ansi_print_help_info(void);

void clear_screen(void)
{
	printf("%s", ANSI_CLEAR);
}

void display_menu(MenuItems const* items, int selected)
{
	clear_screen();
	ansi_print_minimax();
	printf("\n\n\n\t\t\t   Select Option:\n\n");

	int i = 0;
	MenuItems const* p = items;
	while (p->title) {
		if (i == selected) {
			printf("%s", COLOR_BG_BLUE_CURSOR);
		}
		printf("\t\t\t\t%s\n\n", p->title);
		printf("%s", COLOR_WHITE_RESET);
		++p;
		++i;
	}
}

void display_game(Game const* state, int cursor_col)
{
	clear_screen();
	printf("\n\n\t\t   Difficulty: %s", difficulty_items[state->difficulty].title);
	display_grid(state, state->cur_row, cursor_col);
	display_score(state);
	display_turn(state);
}

void display_end_game(Game const* state)
{
	clear_screen();
	ansi_print_game_over();
	display_score(state);
	display_results(state);
	printf("\t\tPress any key to continue...\n\n");
}

void display_help(void)
{
	clear_screen();
	ansi_print_minimax();
	ansi_print_help_info();
	get_user_input();
}

static void display_grid(Game const* state, int cursor_row, int cursor_col)
{
	ansi_print_top_line();

	for (int row = 0; row < BOARD_SIZE; ++row) {
		if (row > 0) {
			ansi_print_mid_line();
		}
		printf("\t%s", ANSI_BOX_VER);
		for (int col = 0; col < BOARD_SIZE; ++col) {
			ansi_print_cell(state, row, col, cursor_row, cursor_col);
		}
		printf("%s", ANSI_BOX_VER);
	}

	ansi_print_bot_line();
}

static void ansi_print_cell(Game const* state, int row, int col, int cursor_row, int cursor_col)
{
	char* color = ansi_get_color(state, row, col);
	if (row == cursor_row && col == cursor_col) {
		color = COLOR_BG_BLUE_CURSOR;
	}

	printf("%s", color);
	if ((*state->board)[row][col].value == 'X') {
		printf("  X");
	} else {
		printf("%3d", (*state->board)[row][col].value);
	}

	printf("%s", COLOR_WHITE_RESET);

	if (col < 9) {
		printf("%s", ANSI_BOX_VER);
	}
}

static void display_score(Game const* state)
{
	printf("\n");
	printf("\t   %s%s", COLOR_CYAN_BOX, ANSI_FRAME_TL);
	for (int i = 0; i < BOX_WIDTH; ++i) {
		printf("%s", ANSI_FRAME_H);
	}
	printf("%s%s\n", ANSI_FRAME_TR, COLOR_WHITE_RESET);
	printf("\t   %s%s%s", COLOR_CYAN_BOX, ANSI_FRAME_V, COLOR_WHITE_RESET);
	printf("  %sSCORE : %-5d%s     %sAI : %-5d%s   ",
		COLOR_GREEN_HUMAN, state->player_score, COLOR_WHITE_RESET,
		COLOR_RED_AI, state->ai_score, COLOR_WHITE_RESET);

	printf("%s%s%s\n", COLOR_CYAN_BOX, ANSI_FRAME_V, COLOR_WHITE_RESET);
	printf("\t   %s%s", COLOR_CYAN_BOX, ANSI_FRAME_BL);
	for (int i = 0; i < BOX_WIDTH; ++i) {
		printf("%s", ANSI_FRAME_H);
	}
	printf("%s%s\n\n", ANSI_FRAME_BR, COLOR_WHITE_RESET);
}

static void display_turn(Game const* state)
{
	if (state->turn == 0) {
		printf("\t\t    It's AI's turn.\n");
	} else {
		printf("\t\t    It's your turn...\n");
	}
}

static void ansi_print_top_line(void)
{
	printf("\n\t%s", ANSI_BOX_TL);
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		if ((i + 1) % 4 == 0) {
			printf("%s", ANSI_BOX_T_TOP);
		} else {
			printf("%s", ANSI_BOX_HOR);
		}
	}
	printf("%s\n", ANSI_BOX_TR);
}

static void ansi_print_mid_line(void)
{
	printf("\n\t%s", ANSI_BOX_T_L);
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		if ((i + 1)  % 4 == 0) {
			printf("%s", ANSI_BOX_CROSS);
		} else {
			printf("%s", ANSI_BOX_HOR);
		}
	}
	printf("%s\n", ANSI_BOX_T_R);
}

static void ansi_print_bot_line(void)
{
	printf("\n\t%s", ANSI_BOX_BL);
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		if ((i + 1)  % 4 == 0) {
			printf("%s", ANSI_BOX_T_BOT);
		} else {
			printf("%s", ANSI_BOX_HOR);
		}
	}
	printf("%s\n", ANSI_BOX_BR);
}

static char* ansi_get_color(Game const* state, int row, int col)
{
	int cur = (int)(*state->board)[row][col].selection;
	if (cur == 1) {
		return COLOR_GREEN_HUMAN;
	} else if (cur == 0) {
		return COLOR_RED_AI;
	}
	if ((state->turn == 1 && state->cur_row == row) ||
		(state->turn == 0 && state->cur_col == col)) {
		return COLOR_ORANGE_ACTIVE;
	}
	return COLOR_WHITE_RESET;
}
static void display_results(Game const* state)
{
	if (state->player_score == state->ai_score) {
		printf("\t\t       %s%s     DRAW     %s\n", COLOR_BG_BLUE_CURSOR, COLOR_BOLD, COLOR_WHITE_RESET);
	} else if (state->player_score > state->ai_score) {
		printf("\t\t      %s%s   YOU WIN!   %s\n", COLOR_BG_GREEN, COLOR_BOLD, COLOR_WHITE_RESET);
	} else {
		printf("\t\t      %s%s   AI WINS    %s\n", COLOR_BG_RED, COLOR_BOLD, COLOR_WHITE_RESET);
	}
	printf("\n\n");
}

static void ansi_print_minimax(void)
{
	printf("\n\n\n\n");
	printf("\t███╗   ███╗██╗███╗   ██╗██╗███╗   ███╗ █████╗ ██╗  ██╗\n");
	printf("\t████╗ ████║██║████╗  ██║██║████╗ ████║██╔══██╗╚██╗██╔╝\n");
	printf("\t██╔████╔██║██║██╔██╗ ██║██║██╔████╔██║███████║ ╚███╔╝ \n");
	printf("\t██║╚██╔╝██║██║██║╚██╗██║██║██║╚██╔╝██║██╔══██║ ██╔██╗ \n");
	printf("\t██║ ╚═╝ ██║██║██║ ╚████║██║██║ ╚═╝ ██║██║  ██║██╔╝ ██╗\n");
	printf("\t╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝\n");
	printf("\n");
}
static void ansi_print_game_over(void)
{
	printf("\n\n\n\n");
	printf("\t    ██████╗  █████╗ ███╗   ███╗███████╗\n");
	printf("\t   ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n");
	printf("\t   ██║  ███╗███████║██╔████╔██║█████╗  \n");
	printf("\t   ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
	printf("\t   ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n");
	printf("\t    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n");

	printf("\t    ██████╗ ██╗   ██╗███████╗██████╗ \n");
	printf("\t   ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
	printf("\t   ██║   ██║██║   ██║█████╗  ██████╔╝\n");
	printf("\t   ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
	printf("\t   ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n");
	printf("\t    ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
}

static void ansi_print_help_info(void)
{
	printf("\t\t          %s%s--- HOW TO PLAY ---%s\n\n", COLOR_CYAN_BOX, COLOR_BOLD, COLOR_WHITE_RESET);

	// Objective
	printf("\t%sOBJECTIVE:%s\n", COLOR_CYAN_BOX, COLOR_WHITE_RESET);
	printf("\t  Collect the highest sum of numbers to beat the AI.\n\n");

	// Mechanics
	printf("\t%sRULES:%s\n", COLOR_CYAN_BOX, COLOR_WHITE_RESET);
	printf("\t  1. You are the %sGREEN%s player. The AI is %sRED%s.\n", COLOR_GREEN_HUMAN, COLOR_WHITE_RESET, COLOR_RED_AI, COLOR_WHITE_RESET);
	printf("\t  2. On your turn, you must select a number from the\n");
	printf("\t     currently active %sROW%s.\n", COLOR_BOLD, COLOR_WHITE_RESET);
	printf("\t  3. The column you choose determines where the AI plays next.\n");
	printf("\t  4. The AI will then select a number from that %sCOLUMN%s,\n", COLOR_BOLD, COLOR_WHITE_RESET);
	printf("\t     which determines your next row.\n");
	printf("\t  5. If a player is %sBLOCKED%s (no valid moves), the game ends\n", COLOR_BOLD, COLOR_WHITE_RESET);
	printf("\t     and they receive a %s-200 point penalty%s.\n\n", COLOR_RED_AI, COLOR_WHITE_RESET);

	// Controls
	printf("\t%sCONTROLS:%s\n", COLOR_CYAN_BOX, COLOR_WHITE_RESET);
	printf("\t  [%s<-%s] Left Arrow   : Move Cursor Left\n", COLOR_BOLD, COLOR_WHITE_RESET);
	printf("\t  [%s->%s] Right Arrow  : Move Cursor Right\n", COLOR_BOLD, COLOR_WHITE_RESET);
	printf("\t  [%sOK%s] Enter/Space  : Select Number\n", COLOR_BOLD, COLOR_WHITE_RESET);
	printf("\t  [%sQ%s ] Quit Game    : Exit to Terminal\n\n", COLOR_BOLD, COLOR_WHITE_RESET);

	printf("\t   %s      Created by: %sshalom2552     %s\n",  COLOR_CYAN_BOX, COLOR_BOLD, COLOR_WHITE_RESET);
	printf("\n\t     Press any key to return to menu...");
	printf("\n");
}


#include "game_logic.h"
#include "game_display.h"
#include "game_input.h"
#include "game_menu.h"
#include "game_random.h"
#include "game_ai.h"

#include <assert.h> // assert
#include <stdio.h>	// printf
#include <stdlib.h> // rand
#include <unistd.h> // sleep

const MenuItems difficulty_items[] = {
	[DIFFICULTY_EASY]	= {.title = "Easy"},
	[DIFFICULTY_MEDIUM]	= {.title = "Medium"},
	[DIFFICULTY_HARD]	= {.title = "Hard"},
	[DIFFICULTY_COUNT]	= {.title = 0},
};

/* Gets the selected cell of the user and update the game state accordenly */
static void handle_player_select(Game* state, int cursor_col);

/* Calls the ai moudle and handle its selection */
static void handle_ai_select(Game* state);

/* cchecks game termination conditions */
static int is_game_over(Game* state);

/* print error message and exit the game */
static void handle_error_event(char* message, Game* state);

/* Handle game over and show game over screen with results */
static void game_over(Game* state);

Difficulty get_game_difficulty(void)
{
	Difficulty selected = (Difficulty)menu_input(difficulty_items, DIFFICULTY_EASY, DIFFICULTY_COUNT);
	return selected;
}

void game_loop(Game* state)
{
	int cursor_col = rand() % BOARD_SIZE; // initial start row
	while (1) {
		display_game(state, cursor_col);
		InputEvent input = get_user_input();

		switch (input) {
			case INPUT_LEFT:
				input_decrement_selecction(&cursor_col, BOARD_SIZE);
				break;
			case INPUT_RIGHT:
				input_increment_selection(&cursor_col, BOARD_SIZE);
				break;
			case INPUT_SELECT:
				handle_player_select(state, cursor_col);
				break;
			case INPUT_QUIT:
				exit_game(state);
			default:
				break;
		}
	}
}

Game* game_create(Difficulty difficulty)
{
	Game* state = malloc(sizeof(Game));
	if (state == NULL) {
		handle_error_event("Cannot allocate memory for the game", NULL);
	}

	state->board = malloc(sizeof(Board));
	if (state->board == NULL) {
		handle_error_event("Cannot allocate memory for the board", NULL);
	}

	state->difficulty = difficulty;
	state->player_score = 0;
	state->ai_score = 0;
	state->cur_row = rand() % BOARD_SIZE;
	state->cur_col = 0;
	state->turn = 1;

	// set board selection to -1 (no selection)
	for (int row = 0; row < BOARD_SIZE; ++row) {
		for (int col = 0; col < BOARD_SIZE; ++col) {
			(*state->board)[row][col].selection = -1;
		}
	}

	generate_gaussian_board(state->board);
	return state;
}

void exit_game(Game* state)
{
	if (state != NULL) {
		free(state->board);
		free(state);
	}
	exit(0);
}

static void handle_player_select(Game* state, int cursor_col)
{
	if ((*state->board)[state->cur_row][cursor_col].value == 'X') {
		return;
	}

	state->player_score += (*state->board)[state->cur_row][cursor_col].value;
	(*state->board)[state->cur_row][cursor_col].value = 'X';
	(*state->board)[state->cur_row][cursor_col].selection = 1;
	state->cur_col = cursor_col;

	state->turn = 0;
	is_game_over(state);
	handle_ai_select(state);
}

static void handle_ai_select(Game* state)
{
	int selected_row = ai_get_selection(state);

	state->ai_score += (*state->board)[selected_row][state->cur_col].value;
	(*state->board)[selected_row][state->cur_col].value = 'X';
	(*state->board)[selected_row][state->cur_col].selection = 0;
	state->cur_row = selected_row;

	state->turn = 1;
	is_game_over(state);
}

static int is_game_over(Game* state)
{
	for (int row = 0; row < BOARD_SIZE; ++row) {
		for (int col = 0; col < BOARD_SIZE; ++col) {
			if ((*state->board)[row][col].value != 'X') {
				goto check_players_move;
			}
		}
	}
	goto game_over;
check_players_move:

	if (state->turn == 1) {
		for (int col = 0; col < BOARD_SIZE; ++col) {
			if ((*state->board)[state->cur_row][col].value != 'X') {
				return 0;
			}
		}
		state->player_score -= BLOCK_PENALTY;
	}
	if (state->turn == 0) {
		for (int row = 0; row < BOARD_SIZE; ++row) {
			if ((*state->board)[row][state->cur_col].value != 'X') {
				return 0;
			}
		}
		state->ai_score -= BLOCK_PENALTY;
	}

game_over:
	game_over(state);
	return 1;
}

static void game_over(Game* state)
{
	display_end_game(state);
	get_user_input();
	exit_game(state);
}

static void handle_error_event(char* message, Game* state)
{
	printf("Error: %s", message);
	exit_game(state);
}


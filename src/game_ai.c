#include "game_ai.h"
#include "game_logic.h"

#include <bits/types/stack_t.h>
#include <stdlib.h> // rand

typedef int (*AiStrategy)(Game* state);

static const AiStrategy strategy[] = {
	[DIFFICULTY_EASY] = strategy_random,
	[DIFFICULTY_MEDIUM] = strategy_greedy,
	[DIFFICULTY_HARD] = strategy_minmax
};

/* Calculates the minmax value in depth 1 */
static int minmax(Game* state, int row, int col);

int ai_get_selection(Game* state)
{
	return strategy[state->difficulty](state);
}

int strategy_random(Game* state)
{
	int options_count = 0;
	int col = state->cur_col;
	int options[BOARD_SIZE] = {0};

	for (int row = 0; row < BOARD_SIZE; ++row) {
		char cur = (*state->board)[row][col].value;
		if (cur != 'X') {
			options[options_count++] = row;
		}
	}
	return options[rand() % options_count];
}

int strategy_greedy(Game* state)
{
	int max_row = -1;
	int is_available = 0;
	int col = state->cur_col;

	for (int row = 0; row < BOARD_SIZE; ++row) {
		char cur = (*state->board)[row][col].value;
		if (cur != 'X') {
			if (!is_available) {
				max_row = row;
			} else if (cur > (*state->board)[max_row][col].value) {
				max_row = row;
			}
			is_available = 1;
		}
	}
	return max_row;
}

int strategy_minmax(Game* state)
{
	// TODO: make recursive
	int max_row = -1;
	int is_available = 0;
	int col = state->cur_col;

	for (int row = 0; row < BOARD_SIZE; ++row) {
		char cur = (*state->board)[row][col].value;
		if (cur != 'X') {
			if (!is_available) {
				max_row = row;
			} else if (minmax(state, row, col) >
				minmax(state, max_row, col)) {
				max_row = row;
			}
			is_available = 1;
		}
	}
	return max_row;
}

int minmax(Game* state, int row, int cur_col)
{
	int max = -200;
	for (int col = 0; col < BOARD_SIZE; ++col) {
		char cur = (*state->board)[row][col].value;
		if ((*state->board)[row][col].value != 'X' && max < cur) {
			max = cur;
		}
	}
	return (*state->board)[row][cur_col].value - max;
}


#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "game_menu.h"	// MenuItems
#define BLOCK_PENALTY 200
#define BOARD_SIZE 10

typedef enum {
	DIFFICULTY_EASY = 0,
	DIFFICULTY_MEDIUM,
	DIFFICULTY_HARD,
	DIFFICULTY_COUNT,
} Difficulty;

extern const MenuItems difficulty_items[];

typedef struct {
	char value;
	int selection;
} Cell;

typedef Cell Board[BOARD_SIZE][BOARD_SIZE];

/* Main game stats */
typedef struct {
	Board* board;
	Difficulty difficulty;

	int player_score;
	int ai_score;

	int turn;
	int cur_row;
	int cur_col;
} Game;

/* Initialize board with random scores.
 *
 * @return Struct with initialize game stats
 */
Game* game_create(Difficulty difficulty);

/*
 * Prompt the user with defifficulty options and update the game stats.
 *
 * @param stats struct with game stats to update
 */

Difficulty get_game_difficulty(void);

/* Main game loop to run the turn based game.
 *
 * @param stats struct holding the game stats
 */
void game_loop(Game* stats);

/* frees all allocated memory and exits the game
 *
 * @param state The game state to free
 */
void exit_game(Game* state);

#endif // GAME_LOGIC_H


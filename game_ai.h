#ifndef AI_H
#define AI_H
#include "game_logic.h"

/* Run the strategy according to game state difficulty and return the selection
 *
 * @param A struct holding the state of the game
 * @return The index of the selected cell
 */
int ai_get_selection(Game* state);

/* AI strategy that selects a random available cell in the ccurrent col
 *
 * @param game The state of the game
 * @return The index of the selected column
 */
int strategy_random(Game* game);

/* AI strategy that selects the max available cell in the ccurrent col
 *
 * @param game The state of the game
 * @return The index of the selected column
 */
int strategy_greedy(Game* game);

/* AI strategy that selects the minmax (depth level 1) available cell in the ccurrent col
 *
 * @param game The state of the game
 * @return The index of the selected column
 */
int strategy_minmax(Game* game);

#endif // AI_H


#ifndef DISPLAY_H
#define DISPLAY_H

#include "game_logic.h" // Game
#include "game_menu.h"	// MenuItems

/* Clear the terminal screen */
void clear_screen(void);

/* Display to the user a simple menu to select the game difficulty.
 *
 * @param cur_selectin The current difficulty selection to highlight
*/
void display_difficulty_menu(int cur_selectin);

/* Display a menu for the user
 *
 * @param items To display in the menu
 * @param Selected The current selection to highlight
 */
void display_menu(MenuItems const* items, int selected);

/* Main function to display the user the current game state.
 *
 * @param state A struct holding the game state
 * @param cursor_col the colomn that the user can select from
*/
void display_game(Game const* state, int cursor_col);

/* Display to the user the  game result screen.
 *
 * @param state A struct holding the game state
*/
void display_end_game(Game const* state);

/* display to the user help page with how to play and game info */
void display_help(void);

#endif // DISPLAY_H


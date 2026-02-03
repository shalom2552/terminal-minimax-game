#ifndef GAME_MENU_H
#define GAME_MENU_H

typedef struct MenuItems {
	char* title;
} MenuItems;

/* Display and get user selection from the items list
 *
 * @param items Options to display and choose from
 * @param selected The deffault selection
 * @param items_count Count of items in the menu
 * @return The selected option from the menu
 */
int menu_input(MenuItems const* items, int selected, int items_count);

/* Increment a the given selection by the boundry
 *
 * @param selected A pointer to the current index of the cursor position
 * @param count The count of items or maximum index allowed
 * @return the new cursor index position
 */
void input_increment_selection(int* selected, int count);

/* Increment a the given selection by the boundry
 *
 * @param selected A pointer to the current index of the cursor position
 * @param count The count of items or maximum index allowed
 * @return the new cursor index position
 */
void input_decrement_selecction(int* selected, int count);

#endif // GAME_MENU_H


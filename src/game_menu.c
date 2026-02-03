#include "game_menu.h"
#include "game_input.h"
#include "game_display.h"
#include "game_logic.h"
#include <unistd.h>

int menu_input(MenuItems const* items, int selected, int items_count)
{
	for (;;) {
		display_menu(items, selected);

		InputEvent input = get_user_input();
		switch (input) {
			case INPUT_DOWN:
				input_increment_selection(&selected, items_count);
				break;
			case INPUT_UP:
				input_decrement_selecction(&selected, items_count);
				break;
			case INPUT_SELECT:
				return selected;
			case INPUT_QUIT:
				exit_game(NULL);
			default:
				break;
		}
	}
}

void input_increment_selection(int* selected, int count)
{
	if (*selected == count - 1) {
		*selected = 0;
		return;
	}
	++(*selected);
}

void input_decrement_selecction(int* selected, int count)
{
	if (*selected == 0) {
		*selected = count;
	}
	--(*selected);
}


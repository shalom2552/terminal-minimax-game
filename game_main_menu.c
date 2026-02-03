#include "game_main_menu.h"

#include "game_display.h"
#include "game_menu.h"
#include <unistd.h>

enum {
	START = 0,
	HELP,
	EXIT,
};

const MenuItems main_menu_items[] = {
	[0]	= {.title = "Start"},
	[1]	= {.title = "Help"},
	[2]	= {.title = "Exit"},
	[3]	= {.title = 0},
};
#define MAIN_MENU_ITEMS_COUNT 3

void main_menu(void)
{
	for (;;) {
		display_menu(main_menu_items, 0);
		int selected = menu_input(main_menu_items, 0, MAIN_MENU_ITEMS_COUNT);
		switch (selected) {
			case START:
				return;
			case HELP:
				display_help();
				break;
			case EXIT:
				exit_game(NULL);
		}
	}
}
// 1. start game -> return 0
// 2. help show help
// 3. quit

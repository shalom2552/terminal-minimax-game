#include "game_logic.h"
#include "game_input.h"
#include "game_main_menu.h"

#include <stdlib.h> // srand
#include <time.h>	// time

int main(void)
{
	srand((unsigned int)time(NULL));
	input_setup();

	main_menu();

	Difficulty difficulity = get_game_difficulty();
	Game* state = game_create(difficulity);

	game_loop(state);

	return 0;
}

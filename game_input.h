#ifndef INPUT_H
#define INPUT_H

typedef enum {
	INPUT_UP,
	INPUT_DOWN,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_SELECT,
	INPUT_QUIT
} InputEvent;

/* called once at the start of the program to save terminal
 * configuration to restore when program exits */
void input_setup(void);

/*
 * Read user action from the terminal.
 * @return enum input action.
 */
InputEvent get_user_input(void);

#endif // INPUT_Hs


#include "game_random.h"
#include "game_logic.h"

#include <math.h>	// sqrt, log, cos
#include <stdlib.h> // rand

#define PI 3.14159265358979323846

#define GAUSSIAN_MEAN	19
#define GAUSSIAN_MAX	42
#define GAUSSIAN_MIN	-13

void generate_gaussian_board(Board* board)
{
	for (int row = 0; row < BOARD_SIZE; ++row) {
		for (int col = 0; col < BOARD_SIZE; ++col) {
			(*board)[row][col].value = (char)generate_gaussian_number(GAUSSIAN_MEAN, GAUSSIAN_MIN, GAUSSIAN_MAX);
		}
	}
}

int generate_gaussian_number(int mean, int min_value, int max_value)
{
	// https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
	double u1 = (double)rand() / RAND_MAX;
	double u2 = (double)rand() / RAND_MAX;

	double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);

	int value = (int)round(z0 * 10.0 + mean);

	if (value < min_value) {
		return min_value;
	} else if (value > max_value) {
		return max_value;
	}

	return value;
}


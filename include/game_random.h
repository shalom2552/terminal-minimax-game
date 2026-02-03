#ifndef RANDOM_H
#define RANDOM_H

#include "game_logic.h"

/* Generate a 10 by 10 board with random numbers from gaussian
*  distribution from -13 to 42 with mean 19.
*
* @param board pointer to board to initialize.
*/
void generate_gaussian_board(Board* board);

/* Generate an integer from a gauusian distribution with mean 19 in range [-13, 42]
 *
 * @param mean The mean of the distribution
 * @param min Minimum value of the distribution
 * @param max Maximum value of the distribution
 * @return A random value from the distribution
 */
int generate_gaussian_number(int mean, int min_value, int max_value);

#endif // RANDOM_H


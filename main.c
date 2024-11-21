#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "queue.h"
#include "stack.h"
#include "rover.h"

int main() {
	t_map map;
	// The following preprocessor directive checks if the code is being compiled on a Windows system.
	// If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
	// On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.

#if defined(_WIN32) || defined(_WIN64)
	map = createMapFromFile("..\\maps\\training.map");
#else
	map = createMapFromFile("../maps/example1.map");
#endif

	// set of random moves available
	t_move *moves = getRandomMoves(9);

	// start localisation
	t_localisation rover = loc_init(6, 5, NORTH);
	printf("test");
	roverRunPhase(rover, map, moves);
	/*rover = move(rover, F_30);
	rover = move(rover, T_LEFT);
	rover = move(rover, F_10);
	rover = move(rover, F_10);
	rover = move(rover, F_10);*/

	roverDisplayInfo(rover,map);
	//check base
	int test = roverCost(rover, map);
	if (test == 0);
	return 0;
}

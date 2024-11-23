#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "queue.h"
#include "stack.h"
#include "rover.h"

void print_menu() {
    printf("\n\nMenu:\n");
    printf("1. Initialize the position of the rover\n");
    printf("2. Display the map, the map cost and the position of the rover on the map\n");
    printf("3. Show tree and best sequence for a phase\n");
    printf("4. Move the rover executing the best movements\n");
    printf("5. Move the rover one movement at a time\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

t_localisation rover_pos(t_map map) {

    // Check if the user is not giving wrong coordinates / direction
    // Use a do while loop

    int x, y, orientation;
    t_localisation rover;

    int counter = 0;

    do {
        if (counter) {
            printf("\nInvalid position. Please Enter again.")
        }
        printf("Enter the initial x-coordinate of the rover: ");
        scanf("%d", &x);
        printf("Enter the initial y-coordinate of the rover: ");
        scanf("%d", &y);
        // Check if you're in the map and not in a crevace
        printf("Enter the orientation of the rover (0 = NORTH, 1 = EAST, 2 = SOUTH, 3 = WEST): ");
        scanf("%d", &orientation);
    } while (
        !(
            0 <= orientation && orientation < 4 
            && 0 <= x  && x < map.x_max 
            && 0 <= y  && y < map.y_max
        )
    );
    rover = loc_init(x, y, (t_orientation) orientation);
    printf("Rover at position (%d, %d) facing ", rover.pos.x, rover.pos.y);
    switch (rover.ori) { // Check if the user is not dumb
        case NORTH: printf("NORTH\n");
            break;
        case EAST: printf("EAST\n");
            break;
        case SOUTH: printf("SOUTH\n");
            break;
        case WEST: printf("WEST\n");
            break;
    }
    return rover;
}

t_localisation move_rover(t_localisation rover, t_node *best) {
    for (int i = 1; i <= best->level; i++) {
        rover = move(rover, best->move);
        printf("N%d : %s -> %d:%d\n", i, getMoveAsString(best->queue[i]->move), best->queue[i]->loc.pos.x,
               best->queue[i]->loc.pos.y);
        fflush(stdout);
    }
    return rover;
}


int main() {
    t_node *best;
    int choice = 5;
    t_localisation rover = loc_init(10, 10, NORTH);
    t_map map;
    t_move *moves = getRandomMoves(9);
    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("example1.map");
#else
	map = createMapFromFile("example1.map");
#endif
    //roverRunPhase(rover, map, moves);
    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                rover = rover_pos();
                break;
            case 2:
                roverDisplayMap(map, rover);

                break;
            case 3:
                // Why showing the whole tree ? Takes time and it's not readable 9 * 8 * 7 * 6 * 5 = total leaves
                // I would have only showed the best path
                best = roverRunPhase(rover, map, moves);
                break;
            case 4: // WHY DOES THE PROGRAM SHUT ? //
                rover = move_rover(rover, best);
                int test_base = roverCost(rover, map);
                if (test_base == 0) {
                    printf("%d", test_base);
                    printf("The rover is at the base station.");
                    fflush(stdout);
                }
                break;
            case 5:
            /*
                int choice;
                printf("Enter a movement to do: (0 = F 10m, 1 = F 20m, 2 = F 30m, 3 = B 10m, 4 = T left, 5 = T right, 6 = U-turn): ");
                scanf("%d", &choice);
            switch (choice) {
                case 0: rover = move(rover,F_10);
                case 1: rover = move(rover,F_20); break;
                case 2: rover = move(rover,F_30); break;
                case 3: rover = move(rover,B_10); break;
                case 4: rover = move(rover,T_LEFT); break;
                case 5: rover = move(rover, T_RIGHT); break;
                case 6: rover = move(rover, U_TURN); break;
            }*/
                printf("DEBUG: NOTHING");
                break;
            case 9:
                // Exit
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 9);

    return 0;
}

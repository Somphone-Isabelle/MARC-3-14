#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "tree.h"
int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    // Initialize MARC's starting position
    t_localisation start_loc = loc_init(2, 1, EAST);
    t_tree *root = tree_node(start_loc, 0, -1, NULL);

    // Build the movement tree
    buildMovementTree(root, &map, 0);

    // Find the optimal path
    t_tree *best_leaf = OptimalLeaf(root);

    if (best_leaf) {
        printf("Optimal path cost: %d\n", best_leaf->cost);
        t_move sequence[5];
        int seq_len;
        moves_sequence(best_leaf, sequence, &seq_len);

        printf("Sequence of moves:\n");
        for (int i = 0; i < seq_len; i++) {
            printf("%s\n", getMoveAsString(sequence[i]));
        }
    }
    free(root);
    return 0;
}


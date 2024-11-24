#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "queue.h"
#include "stack.h"
#include "rover.h"

static int MODE_DEBUG = 0;
static int MAX_MOVES = 9;
static int MIN_COST = 10000;


//si dans map renvoie cout du rover
//if test = 0 we are in the map and we return the cost and the coordinates of the map, if return 1we are outside the map
int roverCost(t_localisation loc, t_map map) {
    int test = roverValidLocalisation(loc, map);
    int cost = 9999;
    if (test == 0) {
        if (MODE_DEBUG == 1) {
            cost = 1;
        } else {
            cost = map.costs[loc.pos.y - 1][loc.pos.x - 1];
        }
        return cost;
    }
    //9999 nous sommes plus dans la map
    return 9999;
}

int roverCostCheck(int cost) {
    if (MODE_DEBUG == 1) {
        return 0;
    }
    //si 9999 nous sommes hors de la carte et si 10000 nous sommes dans une crevasse et donc return 0 si cost valide
    if (cost < 9000) {
        return 0;
    }
    return 1;
}

//verifie si loc valide , renvoie 0 si dans la map et sinon 1
int roverValidLocalisation(t_localisation loc, t_map map) {
    //printf("roverValidLocalisation %d:%d / %d:%d\n", loc.pos.x, loc.pos.y, map.x_max, map.y_max);
    //fflush(stdout);
    if (loc.pos.x > 0 && loc.pos.y > 0 && loc.pos.x <= map.x_max && loc.pos.y <= map.y_max) {
        return 0;
    }
    return 1;
}

//calcul de l'arbre = path de tous les chemins possibles
t_node *roverRunPhase(t_localisation rover, t_map map, t_move *moves) {
    int minCost = 10000;
    int cost = 10000;
    int posx, posy;
    int count = 0; //compteur de noeuds

    t_node *best = malloc(sizeof(t_node));
    t_tree *t1 = malloc(sizeof(t_tree));
    t_node *n0 = malloc(sizeof(t_node));
    n0->loc = rover;
    if (roverValidLocalisation(n0->loc, map) == 0) {
        n0->cost = roverCost(n0->loc, map);
        n0->level = 0;
        n0->queue[0] = n0;
        printf("N0 %05d: %d:%d\t%s\t%d\n", ++count, n0->loc.pos.x, n0->loc.pos.y, " ", n0->cost);
        fflush(stdout);
        t1->node = n0;
        minCost = n0->cost;
        best = n0;
    }

    /* level 1 */
    for (int i1 = 0; i1 < MAX_MOVES; i1++) {
        int p1 = 0;
        if (roverCostCheck(n0->cost) == 0) {
            t_node *n1 = malloc(sizeof(t_node));
            n1->move = moves[i1];
            n1->loc = move(n0->loc, n1->move);
            n1->cost = roverCost(n1->loc, map);
            n1->level = 1;
            n1->queue[0] = n0;
            n1->queue[1] = n1;
            printf("-N1 %05d: %d:%d\t%s\t%d\n", ++count, n1->loc.pos.x, n1->loc.pos.y, getMoveAsString(n1->move),
                   n1->cost);
            fflush(stdout);
            n0->node[i1] = n1;
            if (n1->cost == minCost && n1->level < best->level) {
                best = n1;
            }
            if (n1->cost < minCost) {
                minCost = n1->cost;
                best = n1;
            }


            /* level 2 */
            //still 9 or less possibilities
            for (int i2 = 0; i2 < MAX_MOVES; i2++) {
                int p2 = 0;
                //rest only 8 or less possibilities
                if (i2 != i1 && roverCostCheck(n1->cost) == 0) {
                    t_node *n2 = malloc(sizeof(t_node));
                    n2->move = moves[i2];
                    n2->loc = move(n1->loc, n2->move);
                    n2->cost = roverCost(n2->loc, map);
                    n2->level = 2;
                    n2->queue[0] = n0;
                    n2->queue[1] = n1;
                    n2->queue[2] = n2;
                    printf("--N2 %05d: %d:%d\t%s\t%d\n", ++count, n2->loc.pos.x, n2->loc.pos.y,
                           getMoveAsString(n2->move), n2->cost);
                    fflush(stdout);
                    n1->node[p2++] = n2;
                    if (n2->cost == minCost && n2->level < best->level) {
                        best = n2;
                    }
                    if (n2->cost < minCost) {
                        minCost = n2->cost;
                        best = n2;
                    }

                    /* level 3 */
                    for (int i3 = 0; i3 < MAX_MOVES; i3++) {
                        int p3 = 0;
                        if (i3 != i1 && i3 != i2 && roverCostCheck(n2->cost) == 0) {
                            t_node *n3 = malloc(sizeof(t_node));
                            n3->move = moves[i3];
                            n3->loc = move(n2->loc, n3->move);
                            n3->cost = roverCost(n3->loc, map);
                            n3->level = 3;
                            n3->queue[0] = n0;
                            n3->queue[1] = n1;
                            n3->queue[2] = n2;
                            n3->queue[3] = n3;
                            printf("---N3 %05d: %d:%d\t%s\t%d\n", ++count, n3->loc.pos.x, n3->loc.pos.y,
                                   getMoveAsString(n3->move), n3->cost);
                            fflush(stdout);
                            n2->node[p3++] = n3;
                            if (n3->cost == minCost && n3->level < best->level) {
                                best = n3;
                            }
                            if (n3->cost < minCost) {
                                minCost = n3->cost;
                                best = n3;
                            }

                            /* level 4 */
                            for (int i4 = 0; i4 < MAX_MOVES; i4++) {
                                int p4 = 0;
                                if (i4 != i1 && i4 != i2 && i4 != i3 && roverCostCheck(n3->cost) == 0) {
                                    t_node *n4 = malloc(sizeof(t_node));
                                    n4->move = moves[i4];
                                    n4->loc = move(n3->loc, n4->move);
                                    n4->cost = roverCost(n4->loc, map);
                                    n4->level = 4;
                                    n4->queue[0] = n0;
                                    n4->queue[1] = n1;
                                    n4->queue[2] = n2;
                                    n4->queue[3] = n3;
                                    n4->queue[4] = n4;
                                    printf("----N4 %05d: %d:%d\t%s\t%d\n", ++count, n4->loc.pos.x, n4->loc.pos.y,
                                           getMoveAsString(n4->move), n4->cost);
                                    fflush(stdout);
                                    n3->node[p4++] = n4;
                                    if (n4->cost == minCost && n4->level < best->level) {
                                        best = n4;
                                    }
                                    if (n4->cost < minCost) {
                                        minCost = n4->cost;
                                        best = n4;
                                    }

                                    /* level 5 */
                                    for (int i5 = 0; i5 < MAX_MOVES; i5++) {
                                        int p5 = 0;
                                        if (i5 != i1 && i5 != i2 && i5 != i3 && i5 != i4 && roverCostCheck(n4->cost) ==
                                            0) {
                                            t_node *n5 = malloc(sizeof(t_node));
                                            n5->move = moves[i5];
                                            n5->loc = move(n4->loc, n5->move);
                                            n5->cost = roverCost(n5->loc, map);
                                            n5->level = 5;
                                            n5->queue[0] = n0;
                                            n5->queue[1] = n1;
                                            n5->queue[2] = n2;
                                            n5->queue[3] = n3;
                                            n5->queue[4] = n4;
                                            n5->queue[5] = n5;
                                            printf("-----N5 %05d: %d:%d\t%s\t%d\n", ++count, n5->loc.pos.x,
                                                   n5->loc.pos.y, getMoveAsString(n5->move), n5->cost);
                                            fflush(stdout);
                                            n4->node[p5++] = n5;
                                            if (n5->cost == minCost && n5->level < best->level) {
                                                best = n5;
                                            }
                                            if (n5->cost < minCost) {
                                                minCost = n5->cost;
                                                best = n5;
                                            }
                                        }
                                    } /* level 5 */
                                }
                            } /* level 4 */
                        }
                    } /* level 3 */
                }
            } /* level 2 */
        }
    } /* level 1 */

    printf("count : %d\n", count);

    printf("best level : %d / cost : %d\n", best->level, best->cost);
    printf("N0 : %d:%d\t%s\n", n0->loc.pos.x, n0->loc.pos.y, " ");
    for (int i = 1; i <= best->level; i++) {
        printf("N%d : %s -> %d:%d\n", i, getMoveAsString(best->queue[i]->move), best->queue[i]->loc.pos.x,
               best->queue[i]->loc.pos.y);
        fflush(stdout);
    }
    return best;
}

//affiche la carte avec le rover
void roverDisplayMap(t_map map, t_localisation rover) {
    /** the rules for display are :
     * display all soils with 3x3 characters
     * characters are : B for base station, '-' for plain, '~' for erg, '^' for reg, ' ' for crevasse
     */
    int rx = rover.pos.x - 1;
    int ry = rover.pos.y - 1;
    for (int i = 0; i < map.y_max; i++) {
        for (int rep = 0; rep < 3; rep++) {
            for (int j = 0; j < map.x_max; j++) {
                char c[4];
                if (rx == j && ry == i) {
                    if (rep == 0) {
                        if (rover.ori == NORTH) {
                            strcpy(c, " * ");
                        } else {
                            strcpy(c, "   ");
                        }
                    } else if ((rep == 1)) {
                        if (rover.ori == WEST) {
                            strcpy(c, "*R ");
                        } else if (rover.ori == EAST) {
                            strcpy(c, " R*");
                        } else {
                            strcpy(c, " R ");
                        }
                    } else if ((rep == 2)) {
                        if (rover.ori == SOUTH) {
                            strcpy(c, " * ");
                        } else {
                            strcpy(c, "   ");
                        }
                    }
                } else {
                    switch (map.soils[i][j]) {
                        case BASE_STATION:
                            if (rep == 1) {
                                strcpy(c, " B ");
                            } else {
                                strcpy(c, "   ");
                            }
                            break;
                        case PLAIN:
                            strcpy(c, "---");
                            break;
                        case ERG:
                            strcpy(c, "~~~");
                            break;
                        case REG:
                            strcpy(c, "^^^");
                            break;
                        case CREVASSE:
                            sprintf(c, "%c%c%c", 219, 219, 219);
                            break;
                        default:
                            strcpy(c, "???");
                            break;
                    }
                }

                printf("%s", c);
            }
            printf("\n");
        }
    }
    return;
}

//affiche info du rover (map + cost)
void roverDisplayInfo(t_localisation rover, t_map map) {
    if (roverValidLocalisation(rover, map) == 0) {
        printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
        for (int i = 0; i < map.y_max; i++) {
            for (int j = 0; j < map.x_max; j++) {
                printf("%d ", map.soils[i][j]);
            }
            printf("\n");
        }
        // printf the costs, aligned left 5 digits
        for (int i = 0; i < map.y_max; i++) {
            for (int j = 0; j < map.x_max; j++) {
                printf("%-5d ", map.costs[i][j]);
            }
            printf("\n");
        }
        roverDisplayMap(map, rover);
    }
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "loc.h"
#include "map.h"
#include "moves.h"
#include "queue.h"
#include "stack.h"
#include "rover.h"

static int MAX_MOVES = 9;
static int MIN_COST = 10000;

typedef struct s_node
{
  int nodesize;
  int level;
  t_move move;
  t_localisation loc;
  int cost;
  struct s_node *node[9];
  struct s_node *queue[5];
} t_node;

typedef struct s_tree {
  t_node *node;
} t_tree ;

//si dans map renvoie cout du rover
int roverCost(t_localisation loc, t_map map) {
  int test = roverValidLocalisation(loc, map);
  if (test == 0) {
    int cost = map.costs[loc.pos.y - 1][loc.pos.x - 1];
    return cost;
  }
  return 9999;
}

//verifie si loc valide , renvoie 0 si dans la map et sinon 1
int roverValidLocalisation(t_localisation loc, t_map map)  {
  //printf("roverValidLocalisation %d:%d / %d:%d\n", loc.pos.x, loc.pos.y, map.x_max, map.y_max);
  //fflush(stdout);
  if (loc.pos.x > 0 && loc.pos.y > 0 && loc.pos.x <= map.x_max && loc.pos.y <= map.y_max) {
    return 0;
  }
  return 1;
}

//marche pas encore en cours de debug
void best_tree(t_node* node) {
    if (node == NULL) {
      return;
    }
    t_node *queue = malloc(sizeof(t_node));
    t_node *best = node;
    t_node *tmp;
    for (int level = 0; level < 5; level++) {

      for (int i = 0; i < best->nodesize; i++) {
	tmp = best->node[i];

	printf("N%d : %d:%d\t%s\t%d\n", level, queue->node[level]->loc.pos.x, queue->node[level]->loc.pos.y, getMoveAsString(queue->node[level]->move), queue->node[level]->cost);
	fflush(stdout);

      }
    }

}

//marche pas encore en cours de debug
void print_tree(t_node* node, int level) {
    if (node == NULL) {
      return;
    }

    // Afficher la valeur du nœud avec une indentation correspondant à son niveau
    for (int i = 0; i < level; i++) {
      printf("  "); // Indentation
      fflush(stdout);
    }
    // printf("%d\n", node->cost);
    //    printf("N%d : %d:%d\t%s\t%d\n", level, node->loc.pos.x, node->loc.pos.y, getMoveAsString(node->move), node->cost);
    fflush(stdout);

    if (node->cost < 9000) {
      // Afficher les enfants du nœud
      int max = MAX_MOVES - level;
      for (int i = 0; i < max; i++) {
        print_tree(node->node[i], level + 1); // Appel récursif pour afficher chaque enfant
      }
    }
}

//calcul de l'arbre = path de tous les chemins possibles
void roverRunPhase(t_localisation rover, t_map map, t_move *moves) {
  int minCost = 10000;
  int cost = 10000;
  int posx, posy;
  int count = 0; //compteur de noeuds

  t_tree *t1 = malloc(sizeof(t_tree));
  t_node *n0 = malloc(sizeof(t_node));
  n0->loc = rover;
  if (roverValidLocalisation(n0->loc, map) == 0) {
    n0->cost = roverCost(n0->loc, map);
    n0->level = 0;
    printf("N0 %05d: %d:%d\t%s\t%d\n", ++count, n0->loc.pos.x, n0->loc.pos.y, " ", n0->cost);
    fflush(stdout);
    t1->node = n0;
  }

  /* level 1 */
  for (int i1 = 0; i1 < MAX_MOVES; i1++) {
    int p1 = 0;
    if (n0->cost < 9000) {

      t_node *n1 = malloc(sizeof(t_node));
      n1->move = moves[i1];
      n1->loc = move(n0->loc, n1->move);
      n1->cost = roverCost(n1->loc, map);
      n1->level = 1;

      printf("-N1 %05d: %d:%d\t%s\t%d\n", ++count, n1->loc.pos.x, n1->loc.pos.y, getMoveAsString(n1->move), n1->cost);
      fflush(stdout);
      n0->node[i1] = n1;
      n1->nodesize = i1;

      /* level 2 */
      for (int i2 = 0; i2 < MAX_MOVES; i2++) {
	int p2 = 0;
	if (i2 != i1 && n1->cost < 9000) {
	  t_node *n2 = malloc(sizeof(t_node));
	  n2->move = moves[i2];
	  n2->loc = move(n1->loc, n2->move);
	  n2->cost = roverCost(n2->loc, map);
	  n2->level = 2;
	  printf("--N2 %05d: %d:%d\t%s\t%d\n", ++count, n2->loc.pos.x, n2->loc.pos.y, getMoveAsString(n2->move), n2->cost);
	  fflush(stdout);
	  n1->node[p2++] = n2;
	  n1->nodesize = p2;

	  /* level 3 */
	  for (int i3 = 0; i3 < MAX_MOVES; i3++) {
	    int p3 = 0;
	    if (i3 != i1 && i3 != i2 && n2->cost < 9000) {
	      t_node *n3 = malloc(sizeof(t_node));
	      n3->move = moves[i3];
	      n3->loc = move(n2->loc, n3->move);
	      n3->cost = roverCost(n3->loc, map);
	      n3->level = 3;
	      printf("---N3 %05d: %d:%d\t%s\t%d\n", ++count, n3->loc.pos.x, n3->loc.pos.y, getMoveAsString(n3->move), n3->cost);
	      fflush(stdout);
	      n2->node[p3++] = n3;
	      n2->nodesize = p3;

	      /* level 4 */
	      for (int i4 = 0; i4 < MAX_MOVES; i4++) {
		int p4 = 0;
		if (i4 != i1 && i4 != i2 && i4 != i3 && n3->cost < 9000) {
		  t_node *n4 = malloc(sizeof(t_node));
		  n4->move = moves[i4];
		  n4->loc = move(n3->loc, n4->move);
		  n4->cost = roverCost(n4->loc, map);
		  n4->level = 4;
		  printf("----N4 %05d: %d:%d\t%s\t%d\n", ++count, n4->loc.pos.x, n4->loc.pos.y, getMoveAsString(n4->move), n4->cost);
		  fflush(stdout);
		  n3->node[p4++] = n4;
		  n3->nodesize = p4;

		  /* level 5 */
		  for (int i5 = 0; i5 < MAX_MOVES; i5++) {
		    int p5 = 0;
		    if (i5 != i1 && i5 != i2 && i5 != i3 && i5 != i4 && n4->cost < 9000 ) {
		      t_node *n5 = malloc(sizeof(t_node));
		      n5->move = moves[i5];
		      n5->loc = move(n4->loc, n5->move);
		      n5->cost = roverCost(n5->loc, map);
		      n5->level = 5;
		      printf("-----N5 %05d: %d:%d\t%s\t%d\n", ++count, n5->loc.pos.x, n5->loc.pos.y, getMoveAsString(n5->move), n5->cost);
		      fflush(stdout);
		      n4->node[p5++] =  n5;
		      n4->nodesize = p5;
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
  // best_tree(n0);
}

//affiche la carte avec le rover
void roverDisplayMap(t_map map, t_localisation rover) {
    /** the rules for display are :
     * display all soils with 3x3 characters
     * characters are : B for base station, '-' for plain, '~' for erg, '^' for reg, ' ' for crevasse
     */
    int rx = rover.pos.x - 1;
    int ry = rover.pos.y - 1;
    for (int i = 0; i < map.y_max; i++)
      {
        for (int rep = 0; rep < 3; rep++)
        {
            for (int j = 0; j < map.x_max; j++)
            {
                char c[4];
                if (rx == j && ry == i) {
                    if (rep == 0)  {
                        if (rover.ori == NORTH) {
                            strcpy(c, " * ");
                        } else {
                            strcpy(c, "   ");
                        }
                    } else if ((rep == 1)) {
                        if (rover.ori == WEST) {
                            strcpy(c, " R*");
                        } else if (rover.ori == EAST) {
                            strcpy(c, "*R ");
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
                switch (map.soils[i][j])
                {
                    case BASE_STATION:
                        if (rep==1)
                        {
                            strcpy(c, " B ");
                        }
                        else
                        {
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
                        sprintf(c, "%c%c%c",219,219,219);
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
    for (int i = 0; i < map.y_max; i++)       {
        for (int j = 0; j < map.x_max; j++) 	  {
            printf("%d ", map.soils[i][j]);
	      }
        printf("\n");
      }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)       {
	for (int j = 0; j < map.x_max; j++) 	  {
            printf("%-5d ", map.costs[i][j]);
	  }
        printf("\n");
      }
    roverDisplayMap(map, rover);
  }
}
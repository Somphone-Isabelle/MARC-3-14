//
// Created by Isa 2.0 on 11/11/2024.
//

#ifndef TREE_H
#define TREE_H

#include "loc.h"
#include "moves.h"
#include "map.h"

typedef struct s_tree {
    t_localisation loc;
    t_move move;
    int cost;
    struct s_tree *children[9];
    int nb_children;
    struct s_tree *parent;
} t_tree;

t_tree *tree_node(t_localisation , int, t_move, t_tree*); //root node

void buildMovementTree(t_tree* , t_map*, int); //all possible sequences from the root + each node = state of MARC after sequence of moves
t_tree *OptimalLeaf(t_tree*);
void moves_sequence(t_tree *, t_move sequence[], int *);
void freeTree(t_tree*);

//void display_tree(t_tree);
#endif //TREE_H





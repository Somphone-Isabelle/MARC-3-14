//
// Created by Isa 2.0 on 20/10/2024.
//

#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include "loc.h"
#include "moves.h"
#include "map.h"
#include "queue.h"
#include "stack.h"

typedef struct s_node {
    t_localisation loc;
    t_move move;
    int cost;
    struct s_node *children[5];
} t_node;

t_node* buildTree(t_localisation loc, int depth, t_map map, int num_moves);
t_node* findMinValLeaf(t_node* root);
void PathRootLeaf(t_node* root, t_node* leaf);

#endif //TREE_H

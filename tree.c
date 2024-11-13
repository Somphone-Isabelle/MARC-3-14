
//
// Created by Isa 2.0 on 11/11/2024.
//
#include "tree.h"

t_tree *tree_node(t_localisation loc, int cost, t_move move, t_tree *parent) {
    t_tree *node = (t_tree *)malloc(sizeof(t_tree));
    node->loc = loc;
    node->cost = cost;
    node->parent = parent;
    node->move = move;
    node->nb_children = 0;
    for (int i = 0; i<9 ; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void buildMovementTree(t_tree *root , t_map *map, int max_moves) {
    if (max_moves == 5) {
        return;
    }
    t_move MoveAvails[9];
    ChooseRandMove(MoveAvails,9);

    for (int i = 0; i<9; i++) {
        t_localisation new_loc = move(root->loc, MoveAvails[i]);
        if(isValidLocalisation(new_loc.pos,map->x_max, map->y_max)) {
            int map_cost = map->costs[new_loc.pos.x][new_loc.pos.y];
            if (map_cost >= 10000) { //ignore crevasse
                continue;
            }
            int new_cost = root->cost + map_cost;
            t_tree *child = tree_node(new_loc, new_cost, MoveAvails[i], root);
            root->children[root->nb_children++] = child;
            buildMovementTree(child, map, max_moves+1);
        }
    }
}



t_tree *OptimalLeaf(t_tree *root) {
    t_tree *best_leaf = NULL;
    int min_cost = COST_UNDEF;
    if (root->nb_children == 0) {
        return root;
    }
    for (int i = 0; i<root->nb_children; i++) {
        t_tree *leaf = OptimalLeaf(root->children[i]);
        if (leaf && leaf->cost < min_cost) {
            min_cost = leaf->cost;
            best_leaf = leaf;
        }
    }
    return best_leaf;
}

void moves_sequence(t_tree *leaf, t_move sequence[], int *length) {
    t_tree *curr = leaf;
    int index = 0;
    while (curr && curr->move != -1) {
        sequence[index++] = curr->move;
        curr = curr -> parent;
    }
    *length = index;
    for (int i = 0; i < index / 2; i++) {
        t_move temp = sequence[i];
        sequence[i] = sequence[index - i - 1];
        sequence[index - i - 1] = temp;
    }
}

void freeTree(t_tree *node) {
    if (!node) return;

    for (int i = 0; i < node->nb_children; i++) {
        freeTree(node->children[i]);
    }
    free(node);
}
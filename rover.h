//
// Created by Isa School on 21/11/2024.
//



#ifndef ROVER_H
#define ROVER_H
typedef struct s_node
{
    int level;
    t_move move;
    t_localisation loc;
    int cost;
    struct s_node *node[9];
    struct s_node *queue[6];
} t_node;

typedef struct s_tree {
    t_node *node;
} t_tree ;


void roverPhaseMove(t_localisation, t_map, t_move *);
t_node * roverRunPhase(t_localisation, t_map, t_move *);
void roverDisplayMap(t_map, t_localisation);
void roverDisplayInfo(t_localisation, t_map);
int roverValidLocalisation(t_localisation, t_map);
int roverCost(t_localisation, t_map);
#endif //ROVER_H

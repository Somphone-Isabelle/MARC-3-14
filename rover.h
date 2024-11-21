//
// Created by Isa School on 21/11/2024.
//

#ifndef ROVER_H
#define ROVER_H
void roverPhaseMove(t_localisation, t_map, t_move *);
void roverRunPhase(t_localisation, t_map, t_move *);
void roverDisplayMap(t_map, t_localisation);
void roverDisplayInfo(t_localisation, t_map);
int roverValidLocalisation(t_localisation, t_map);
int roverCost(t_localisation, t_map);
#endif //ROVER_H

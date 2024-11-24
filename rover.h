//
// Created by Isa School on 21/11/2024.
//


#ifndef ROVER_H
#define ROVER_H

/**
 * @brief Represents a single node in the tree structure for rover pathfinding.
 *        Each node contains information about the move, location, cost, and connections to child nodes.
 * @param level : the depth level of this node in the tree (starting from 0).
 * @param move : the move taken to reach this node.
 * @param loc : the location of the rover at this node.
 * @param cost : the cost associated with reaching this node.
 * @param node : an array of pointers to child nodes representing subsequent moves.
 * @param queue : an array representing the path sequence from the root node to this node.
 */
typedef struct s_node {
    int level;
    t_move move;
    t_localisation loc;
    int cost;
    struct s_node *node[9];
    struct s_node *queue[6];
} t_node;

/**
 * @brief Represents the tree structure for rover pathfinding.
 *        Contains the root node of the tree.
 * @param node : the root node of the tree, representing the initial position and state of the rover.
 */
typedef struct s_tree {
    t_node *node;
} t_tree;

/**
 *@brief computes all possible paths for the rover from its current position using a tree structure
 *@param rover : the initial location and orientation of the rover
 *@param map : the map containing terrain and movement costs
 *@param moves : an array of possible moves the rover can make
 * @return a pointer to the best node(path) in the computed tree
 */
t_node *roverRunPhase(t_localisation rover, t_map map, t_move *moves);

/**
 *@brief Displays the map with the rover's current position and orientation
 *@param map : the map to display
 *@param rover : the rover's position and orientation to highlight on the map
 */
void roverDisplayMap(t_map, t_localisation);

/**
 *@brief Displays detailes information about the map and the rover's current state
 *@param rover : the rover's current location and orientation
 *@param map : the map being used
 */
void roverDisplayInfo(t_localisation rover, t_map map);

/**
 *@brief Verifies whether the rover's current location is within the map bounds.
 *@param loc : the pos to validate
 *@param map : the map defining the valid bounds
 * @return 0 if loc valid, 1 outside the map
 */
int roverValidLocalisation(t_localisation loc, t_map map);


/**
 * @brief : verify that the rover is in the map with its associated cost
 * @param loc : loc of the rover
 * @param map : map where is the rover
 * @return cost if the rover is in the map, 9999 else
 */
int roverCost(t_localisation loc, t_map map);

/**
 * @brief : checks if the cost is valid for rover movement
 * @param cost : the movement cost to check
 * @return return 0 if cost valid < 9000, 1 otherwise
 */
int roverCostCheck(int cost);
#endif //ROVER_H

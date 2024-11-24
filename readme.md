# Rover run! - TI301 Project
    Group : INT 3
    Team : 14
    Members : 
        * Isabelle SOMPHONE
        * Inès VEIGNEAU
        * Jessica MILLOGO

## Storyline
    2028: A very intense solar storm has just hit... The MARC MArs Rover Cartograph rover, which was carrying out its mission very well, has suffered a malfunction. Its programming, guidance and movement systems have been seriously affected...
    The ESTF, Efrei Space Task Force, has called on programming experts to design new travel software for MARC.
    Your mission is to use this travel software to brinng MARC back to a base station where it can be refurbished.

## Our vision
    For an optimized trial of our program, our main file gives access to a menu composed of the following choices :
        1. Initialize the position of the rover
            Calling the function "loc_init(int, int, t_orientation)" this option allows the user to input the rover's coordinates and orientation inside the map boundaries.
        2. Display the map, the map cost and the position of the rover on the map
            This option redirects the user to the function "roverDisplayMap(t_map, t_localisation)" printing the map updated with the position of the rover(*R).
        3. Compute and show moves tree and best sequence for a phase
            This option redirects the user to the function "roverRunPhase(t_localisation, t_map, t_move *)" printing every move the rover could make from the position it is at to the position it would reach in 5 moves, and the best possible sequence for the rover.
        4. Move the rover executing the best sequence
            This option redirects the user to the function "move_rover(t_localisation, t_node *)" that moves the rover according to the best sequence previously chosen and updates its position on the map.
        5. Move the rover one movement at a time
            This option redirects the user to the function "single_move(t_localisation)" and "roverDisplayMap(t_map, t_localisation)" that allows the user to move the rover however fits them best followed by the display oof the map and the coordinates of the rover.
        6. Draw the 9 moves at random
            This option redirects the user to the function "getRandomMoves(int)" that creates a knew array of random movements to chose from.
        9.Exit
            This option stops the execution of the program completely, allowing the rover to get a day off.

## Conclusion
    This practical helped us understand how to implement tree structures, understand complexity and how lists can be used in a working environment.
    Thank you for assisting us during this project and we hope you aprreciated it !
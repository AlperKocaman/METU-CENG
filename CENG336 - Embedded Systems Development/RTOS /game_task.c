/* 
Yavuz Selim YESILYURT - 2259166
Alper KOCAMAN - 2169589
*/

/**********************************************************************
 *---------------------------PURPOSE OF THE GAME TASK------------------
 	- sending proper map commands
 	- sending proper turning right, move forward or turning left commands
 	- if whole map is discovered, changing the algorithm to following left border
 	- if whole map is discovered, not sending map commands
 **********************************************************************/

/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS EXPLANATIONS ---------------
 followRightBorder() -> implements algorithm to enable robot folows right border
 followLefttBorder() -> implements algorithm to enable robot folows left border(for bonus)
 updateSituation()   -> sends proper map and end comments
 **********************************************************************/

#include "common.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/

char trBuffer[SIZE_TM_BUF]; 						// holds the bytes to be transmitted 
char map[4][16]; 									// currently updated map array
int first = 1; 										// used for the first movement after the map completed
extern char systemState; 							// state of the system; S_IDLE or S_ACTIVE
extern char robotSituation; 						// current robot movement ; turning right, turning left or moving  
extern int encoderValue, front, right, rear, left; 	// variables for encoder responses
extern short internalSum, robotDegree; 				// robot's location and degree info are kept in these variables
extern int visited; 								// currently visited cell count 
extern int x, y; 									// using for robot coordinates


/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/
 
void followRightBorder() {
	/* Function for determining next move after a stop */

	if ((robotDegree == 180 && y != 0 && map[x][y-1] == ' ') || (robotDegree == 90 && x != 3 && map[x+1][y] == ' ') || 
		(robotDegree == 0 && y != 15 && map[x][y+1] == ' ') || (robotDegree == 270 && x != 0 && map[x-1][y] == ' '))  {
		// if there are no obstacles to right
		//     then TURN RIGHT and MOVE FORWARD 
		robotSituation = TURNING_RIGHT;     
		trBuffer[0] = '$';
		trBuffer[1] = 'R';
		trBuffer[2] = ':';
		// trBuffer has "$R:" now
        transmitBuffer_push(trBuffer,3);
	}

	else if ((robotDegree == 180 && x != 3 && map[x+1][y] == ' ') || (robotDegree == 90 && y != 15 && map[x][y+1] == ' ') ||
	 (robotDegree == 0 && x != 0 && map[x-1][y] == ' ') || (robotDegree == 270 && y != 0 && map[x][y-1] == ' ')) {
		// else if there are no obstacles in front of robot 
		//     then MOVE FORWARD 
	    robotSituation = MOVING;
		trBuffer[0] = '$';
		trBuffer[1] = 'F';
		trBuffer[2] = ':';
		// trBuffer has "$F:" now
		transmitBuffer_push(trBuffer,3);
	}

	else {
		// there are obstacles on both right and front of the robot, the only choice is left now 
		//     TURN LEFT
		robotSituation = TURNING_LEFT;
		trBuffer[0] = '$';
		trBuffer[1] = 'L';
		trBuffer[2] = ':';
		// trBuffer has "$L:" now
		transmitBuffer_push(trBuffer,3);
	}
}

void followLeftBorder() {
	/* Purpose of this function is that make robot faster to return target cell before time limit exceeds*/
	/* In order to following right border, this function makes robot to follow left border*/
	/* Function for determining next move after a stop when whole map is explored, robot is moving for bonus case */

	if ((robotDegree == 180 && y != 15 && map[x][y+1] == ' ') || (robotDegree == 90 && x != 0 && map[x-1][y] == ' ') || 
		(robotDegree == 0 && y != 0 && map[x][y-1] == ' ') || (robotDegree == 270 && x != 3 && map[x+1][y] == ' '))  {
		// if there are no obstacles to left
		//     then TURN LEFT and MOVE FORWARD 
		robotSituation = TURNING_LEFT;
		trBuffer[0] = '$';
		trBuffer[1] = 'L';
		trBuffer[2] = ':';
		// trBuffer has "$L:" now
		transmitBuffer_push(trBuffer,3);
	}

	else if ((robotDegree == 180 && x != 3 && map[x+1][y] == ' ') || (robotDegree == 90 && y != 15 && map[x][y+1] == ' ') ||
	 (robotDegree == 0 && x != 0 && map[x-1][y] == ' ') || (robotDegree == 270 && y != 0 && map[x][y-1] == ' ')) {
		// else if there are no obstacles in front of you 
		//     then MOVE FORWARD 
	    robotSituation = MOVING;
		trBuffer[0] = '$';
		trBuffer[1] = 'F';
		trBuffer[2] = ':';
		// trBuffer has "$F:" now
		transmitBuffer_push(trBuffer,3);
	}

	else {
		// there are obstacles on both left and front of the robot, the only choice is right now 
		// TURN RIGHT
        robotSituation = TURNING_RIGHT;     
        trBuffer[0] = '$';
		trBuffer[1] = 'R';
		trBuffer[2] = ':';
		// trBuffer has "$R:" now
        transmitBuffer_push(trBuffer,3);
	}
}

void updateSituation() {
	/* Function for transmission of new command according to current robot situation */

	if(systemState == S_ACTIVE) {

		// System took "$GO:" command and becomes active
        
		if (robotSituation == MOVING) {
			// CARRY ON MOVING FORWARD....
			trBuffer[0] = '$';
			trBuffer[1] = 'F';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
		else if (robotSituation == TURNING_RIGHT) {
			// CARRY ON TURNING RIGHT....
			trBuffer[0] = '$';
			trBuffer[1] = 'R';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
		else if (robotSituation == TURNING_LEFT) {
			// CARRY ON TURNING LEFT....
			trBuffer[0] = '$';
			trBuffer[1] = 'L';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
		else if (robotSituation == STOPPED) { 
			// Robot has stopped earlier, determine next move
                
            if(visited != 62 || first) {

            	/* Map is not explored totaly, new MAP commands should be sent*/
                /* First Send newly explored cells MAP commands */
            	/* Map command is sent considering with type of the cell
				There are 3 types of cells 
				1- cells that are on the 4 corners of the map
				2- cells that are on the edges except 4 corners of the map	
				3- inside cells
				*/

                if (x == 0 && y == 0) {

                    // both at border type-1
                	
                    // below cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x+1; // X
                    trBuffer[3] = y; // Y
                    if (map[x+1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // right cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y+1; // Y
                    if (map[x][y+1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else if (x == 0 && y == 15) {

                    // both at border type-2

                    // below cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x+1; // X
                    trBuffer[3] = y; // Y
                    if (map[x+1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // left cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y-1; // Y
                    if (map[x][y-1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else if (x == 3 && y == 0) {
                    // both at border type-3

                    // above cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x-1; // X
                    trBuffer[3] = y; // Y
                    if (map[x-1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // right cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y+1; // Y
                    if (map[x][y+1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else if (x == 3 && y == 15) {
                    // both at border type-4

                    // above cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x-1; // X
                    trBuffer[3] = y; // Y
                    if (map[x-1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // left cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y-1; // Y
                    if (map[x][y-1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else if (x == 0) {
                    // only x border type-1

                    // left cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y-1; // Y
                    if (map[x][y-1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // right cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y+1; // Y
                    if (map[x][y+1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // below cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x+1; // X
                    trBuffer[3] = y; // Y
                    if (map[x+1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else if (x == 3) {
                    // only x border type-2

                    // left cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y-1; // Y
                    if (map[x][y-1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // right cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y+1; // Y
                    if (map[x][y+1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // above cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x-1; // X
                    trBuffer[3] = y; // Y
                    if (map[x-1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else if (y == 0) {
                    // only y border type-1

                    // above cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x-1; // X
                    trBuffer[3] = y; // Y
                    if (map[x-1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // below cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x+1; // X
                    trBuffer[3] = y; // Y
                    if (map[x+1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // right cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y+1; // Y
                    if (map[x][y+1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else if (y == 15) {
                    // only y border type-2

                    // above cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x-1; // X
                    trBuffer[3] = y; // Y
                    if (map[x-1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // below cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x+1; // X
                    trBuffer[3] = y; // Y
                    if (map[x+1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // left cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y-1; // Y
                    if (map[x][y-1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }

                else {
                    // Normal cell case -- in the middle of the map - no borders

                    // above cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x-1; // X
                    trBuffer[3] = y; // Y
                    if (map[x-1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // below cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x+1; // X
                    trBuffer[3] = y; // Y
                    if (map[x+1][y] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // right cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y+1; // Y
                    if (map[x][y+1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);

                    // left cell
                    trBuffer[0] = '$';
                    trBuffer[1] = 'M';
                    trBuffer[2] = x; // X
                    trBuffer[3] = y-1; // Y
                    if (map[x][y-1] == ' ')
                        trBuffer[4] = 0; // S
                    else
                        trBuffer[4] = 1; // S
                    trBuffer[5] = ':';
                    transmitBuffer_push(trBuffer,6);
                }
                /*if whole 62 cells are visited, last time to do followRightBorder algorithm. From that point, robot will use followLeftBorder algorithm.*/

                if (visited == 62)
                    first = 0;
                else
                    followRightBorder();
            }
            
            else if ( (x==0) && (y==15)) {
				// Robot is inside of the target point, "$END:" command can be sent.
				// END
				trBuffer[0] = '$';
				trBuffer[1] = 'E';
				trBuffer[2] = 'N';
				trBuffer[3] = 'D';
				trBuffer[4] = ':';
				transmitBuffer_push(trBuffer,5);
                systemState = S_IDLE;
			}
			/* Algorithm to make robot faster when returning back to the target point*/
            else 
                followLeftBorder();
		}
		else {
			/* robotSituation == CANSTOP */
            robotSituation = STOPPED;
            trBuffer[0] = '$';
			trBuffer[1] = 'S';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
	} 
    
    /* Simulator IDLE */
}

/**********************************************************************
 * ------------------------------ Naive Update Situation -------------------------------
 * 
 * This is the naive update situation function which doesn't implement bonus cases.
 * It stops when all cells in the map are explored  
 * The purpose of putting this function here is, if robot is able to discover whole cells and do the main task however it is not able to arrive target point before 
 time exceeds, you can take the comments in this function(and put comments the actual updateSituation() function) and see that robot is able to do main task. 
 *
 **********************************************************************/
/*
void updateSituation() {
	// Function for transmission of new command according to current robot situation

	if(systemState == S_ACTIVE) {
		if (robotSituation == MOVING) {
			// CARRY ON MOVING FORWARD....
            
			trBuffer[0] = '$';
			trBuffer[1] = 'F';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
		else if (robotSituation == TURNING_RIGHT) {
			// CARRY ON TURNING RIGHT....
			trBuffer[0] = '$';
			trBuffer[1] = 'R';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
		else if (robotSituation == TURNING_LEFT) {
			// CARRY ON TURNING LEFT....
			trBuffer[0] = '$';
			trBuffer[1] = 'L';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
		else if (robotSituation == STOPPED) { 
			// Robot has stopped earlier, determine next move

            // First Send newly explored cells MAP commands
            if (x == 0 && y == 0) {
                // both at border type-1

                // below cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x+1; // X
                trBuffer[3] = y; // Y
                if (map[x+1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // right cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y+1; // Y
                if (map[x][y+1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else if (x == 0 && y == 15) {
                // both at border type-2

                // below cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x+1; // X
                trBuffer[3] = y; // Y
                if (map[x+1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // left cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y-1; // Y
                if (map[x][y-1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else if (x == 3 && y == 0) {
                // both at border type-3

                // above cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x-1; // X
                trBuffer[3] = y; // Y
                if (map[x-1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // right cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y+1; // Y
                if (map[x][y+1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else if (x == 3 && y == 15) {
                // both at border type-4

                // above cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x-1; // X
                trBuffer[3] = y; // Y
                if (map[x-1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // left cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y-1; // Y
                if (map[x][y-1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else if (x == 0) {
                // only x border type-1

                // left cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y-1; // Y
                if (map[x][y-1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // right cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y+1; // Y
                if (map[x][y+1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // below cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x+1; // X
                trBuffer[3] = y; // Y
                if (map[x+1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else if (x == 3) {
                // only x border type-2

                // left cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y-1; // Y
                if (map[x][y-1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // right cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y+1; // Y
                if (map[x][y+1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // above cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x-1; // X
                trBuffer[3] = y; // Y
                if (map[x-1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else if (y == 0) {
                // only y border type-1

                // above cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x-1; // X
                trBuffer[3] = y; // Y
                if (map[x-1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // below cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x+1; // X
                trBuffer[3] = y; // Y
                if (map[x+1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // right cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y+1; // Y
                if (map[x][y+1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else if (y == 15) {
                // only y border type-2

                // above cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x-1; // X
                trBuffer[3] = y; // Y
                if (map[x-1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // below cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x+1; // X
                trBuffer[3] = y; // Y
                if (map[x+1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // left cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y-1; // Y
                if (map[x][y-1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }

            else {
                // Normal cell case -- in the middle of the map - no borders

                // above cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x-1; // X
                trBuffer[3] = y; // Y
                if (map[x-1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // below cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x+1; // X
                trBuffer[3] = y; // Y
                if (map[x+1][y] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // right cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y+1; // Y
                if (map[x][y+1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);

                // left cell
                trBuffer[0] = '$';
                trBuffer[1] = 'M';
                trBuffer[2] = x; // X
                trBuffer[3] = y-1; // Y
                if (map[x][y-1] == ' ')
                    trBuffer[4] = 0; // S
                else
                    trBuffer[4] = 1; // S
                trBuffer[5] = ':';
                transmitBuffer_push(trBuffer,6);
            }
            
            if (visited == 62) {
				// END 
				trBuffer[0] = '$';
				trBuffer[1] = 'E';
				trBuffer[2] = 'N';
				trBuffer[3] = 'D';
				trBuffer[4] = ':';
				transmitBuffer_push(trBuffer,5);
                systemState = S_IDLE;
			}
            else
                followRightBorder();
		}
		else {
			// robotSituation == CANSTOP
            robotSituation = STOPPED;
            trBuffer[0] = '$';
			trBuffer[1] = 'S';
			trBuffer[2] = ':';
			transmitBuffer_push(trBuffer,3);
		}
	} 
    // Simulator IDLE 
}
*/


/**********************************************************************
 * ------------------------------ GAME_TASK -------------------------------
 * 
 * Implements the algorithm and transmits the required commands to simulator
 * 
 **********************************************************************/
TASK(GAME_TASK) 
{
    short int i;
    
	PIE1bits.RC1IE = 1;	// enable USART receive interrupt

	/* Initialize map with 62 X values and 2 ' ' values*/
   
    map[0][0] = ' ';
    map[0][15] = ' ';
    for (i = 1; i < 15 ; i++)
        map[0][i] = 'X';
    
    for (i = 0; i < 16 ; i++)
        map[1][i] = 'X';
    
    for (i = 0; i < 16 ; i++)
        map[2][i] = 'X';
    
    for (i = 0; i < 16 ; i++)
        map[3][i] = 'X';
    
	SetRelAlarm(GAME_ALARM, 10, 70);
	/* This is the alarm that triggers updateSituation function with average of 70 ms*/
	while(1) {
        WaitEvent(ALARM_EVENT);
        ClearEvent(ALARM_EVENT);
        updateSituation();
	}
	TerminateTask();
}


/* End of File : game_task.c */
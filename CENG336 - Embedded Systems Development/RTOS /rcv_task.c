/* 
Yavuz Selim YESILYURT - 2259166
Alper KOCAMAN - 2169589
*/

/**********************************************************************
 *---------------------------PURPOSE OF THE RCV TASK------------------
 	- taking proper encoder responses
 	- taking proper sensor responses
 **********************************************************************/

/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS EXPLANATIONS ---------------
 parseResponse() -> takes the response and recognizes it
 	- if response is "go", start robot 
 	- if response is starting with "E", this is an encoder response and parse it to take N value
 	- if response is starting with "D", this is a  sensor  response and parse it to take XYZT values
 **********************************************************************/

#include "common.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
char rcvBuffer[SIZE_RC_BUF]; 						// holds the bytes to be received
char data_size;          							// received data size taken to this register
extern char systemState; 							// state of the system; S_IDLE or S_ACTIVE
extern char robotSituation; 						// current robot movement ; turning right, turning left or moving
extern char map[4][16];								// currently updated map array
extern int encoderValue, front, right, rear, left; 	// variables for encoder responses
extern short internalSum, robotDegree; 				// robot's location and degree info are kept in these variables
extern int visited; 								// currently visited cell count 
extern int x, y; 									// using for robot coordinates
/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/

void parseResponse(){
    
    data_size = receiveBuffer_pop(rcvBuffer);
    
    if(!data_size) 
        return ;

	if(rcvBuffer[0] == 'G' && rcvBuffer[1] == 'O'){
		// GO Received! Start the game!
        systemState = S_ACTIVE;
        robotSituation = CANSTOP;

	}

	else if (rcvBuffer[0] == 'E') {

		// An Encoder response received  
		// N value describes the number that whether pixel numbers robot should move or degrees that robot should turn

		// robotSituation is updated if TURNING/MOVING operations are done
		// IF TURNING_RIGHT ENDS THEN DIRECTLY MOVE IT TO MOVING if whole map is not explored
		// IF TURNING_LEFT  ENDS THEN DIRECTLY MOVE IT TO MOVING if whole map is explored for bonus cases

		encoderValue = rcvBuffer[1];
		
		if(robotSituation == MOVING)
			internalSum += encoderValue;
		// update internal pixel position   

		else if(robotSituation == TURNING_RIGHT){
			robotDegree += encoderValue;
		// update robot degree
		}

		else if(robotSituation == TURNING_LEFT)
			robotDegree -= encoderValue;
		// update robot degree

		if (internalSum == 50) // robot is in the center of the cell
			internalSum = 0;

		if(robotDegree >= 360) // for boundary checks
			robotDegree -= 360;

		else if(robotDegree < 0) // for boundary checks
			robotDegree += 360;

        
		if(((robotDegree==0) || (robotDegree==90) || (robotDegree==180) || (robotDegree==270) ) && !internalSum){

			/*robot situation can be changed in here */

			if( (robotSituation == TURNING_RIGHT) && (visited != 62))
				robotSituation = MOVING ;
            
            else if((robotSituation == TURNING_LEFT) && (visited == 62))
                robotSituation = MOVING ;

			else {

				/* robot coordinates should be updated here*/
                if (robotSituation == MOVING){
                    if(robotDegree==0)
                        x-- ;
                    else if(robotDegree==90)
                        y++ ;
                    else if(robotDegree==180)
                        x++ ;
                    else
                        y--;
                }
                robotSituation = CANSTOP ; // robot can send stop command to perceive surroundings
            }
        }
        
        //****************************************************************************************//
        //* This commented if structure has been put here
        //* Purpose is the same in the game task (commented updateSituaiton function is placed)
        //* If robot is moving after discovered all the cells for bonus cases and time exceeds,
        //* This commented if structure can be replaced by above one to show that main task can be done  
        //****************************************************************************************//

        /*
        if(((robotDegree==0) || (robotDegree==90) || (robotDegree==180) || (robotDegree==270) ) && !internalSum) {

			if(robotSituation == TURNING_RIGHT)
				robotSituation = MOVING ;

			else {
                if (robotSituation == MOVING){
                    if(robotDegree==0)
                        x-- ;
                    else if(robotDegree==90)
                        y++ ;
                    else if(robotDegree==180)
                        x++ ;
                    else
                        y--;
                }
                robotSituation = CANSTOP ;
            }
        }
        */
	}

	else if (rcvBuffer[0] == 'D') {

		// A Sensor response received  
		// 'XYZT' values are taken according to degree of robot

		// Map array is updated
		// FOR ALL X values seen in the map,  change to actual value (can be '|' or ' ') and increment map visited

		front = rcvBuffer[1];
		right = rcvBuffer[2];
		rear  = rcvBuffer[3];
		left  = rcvBuffer[4];

		// If 'X' is seen in the map, change that to '|' or ' '

		if(robotDegree == 90){

			if (x != 3) {
				if (map[x+1][y] == 'X')
					visited++;
				map[x+1][y] = right?255 :' ' ;
			}
			if (y != 0) {
				if (map[x][y-1] == 'X')
					visited++;
				map[x][y-1] = rear ?255 :' ' ;
			}
			if (x != 0) {
				if (map[x-1][y] == 'X')
					visited++;
				map[x-1][y] = left ?255 :' ' ;
			}
			if (y != 15) {
				if (map[x][y+1] == 'X')
					visited++;
				map[x][y+1] = front?255 :' ' ;
			}
		}

		else if(robotDegree == 180){
			
			if (x != 3){
				if (map[x+1][y] == 'X')
					visited++;
				map[x+1][y] = front?255 :' ' ;
			}
			if (y != 0) {
				if (map[x][y-1] == 'X')
					visited++;
				map[x][y-1] = right?255 :' ' ;
			}
			if (x != 0) {
				if (map[x-1][y] == 'X')
					visited++;
				map[x-1][y] = rear ?255 :' ' ;
			}
			if (y != 15) {
				if (map[x][y+1] == 'X')
					visited++;
				map[x][y+1] = left ? 255 :' ' ;
			}
		}

		else if(robotDegree == 270){

			if (x != 3) {
				if (map[x+1][y] == 'X')
					visited++;
				map[x+1][y] = left ? 255 :' ' ;
			}
			if (y != 0) {
				if (map[x][y-1] == 'X')
					visited++;
				map[x][y-1] = front? 255:' ' ;
			}
			if (x != 0) {
				if (map[x-1][y] == 'X')
					visited++;
				map[x-1][y] = right? 255 :' ' ;
			}
			if (y != 15) {
				if (map[x][y+1] == 'X')
					visited++;
				map[x][y+1] = rear ?255 :' ' ;
			}
		}

		else{
			
			if (x != 3) {
				if (map[x+1][y] == 'X')
					visited++;
				map[x+1][y] = rear ?255 :' ' ;
			}
			if (y != 0) {
				if (map[x][y-1] == 'X')
					visited++;
				map[x][y-1] = left ?255 :' ' ; 
			}
			if (x != 0) {
				if (map[x-1][y] == 'X')
					visited++;
				map[x-1][y] = front?255 :' ' ;
			}
			if (y != 15) {
				if (map[x][y+1] == 'X')
					visited++;
				map[x][y+1] = right?255 :' ' ;
			}
		}
	}
}

/**********************************************************************
 * ------------------------------ RCV TASK -------------------------------
 * 
 * Receives & Parses the simulator response + Updates the robot
 * 
 **********************************************************************/
TASK(RCV_TASK) 
{
    //PIE1bits.TX1IE = 1;	// enable USART transmit interrupt
	PIE1bits.RC1IE = 1;	// enable USART receive interrupt
    
    SetRelAlarm(RECEIVE_ALARM, 1, 70); // this is the alarm that triggers receive task
	while(1) {
        WaitEvent(ALARM_EVENT);
        ClearEvent(ALARM_EVENT);
        parseResponse();
	}
	TerminateTask();
}

/* End of File : rcv_task.c */
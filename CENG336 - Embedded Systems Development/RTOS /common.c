/* 
Yavuz Selim YESILYURT - 2259166
Alper KOCAMAN - 2169589
*/

#include "common.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/

unsigned char transmitBuffer_popPtr = 0;  	// internal transmit buffer's pop index       
unsigned char transmitBuffer_pushPtr = 0; 	// internal transmit buffer's push index
unsigned char receiveBuffer_popPtr = 0; 	// internal receive buffer's pop index
unsigned char receiveBuffer_pushPtr = 0; 	// internal receive buffer's push index
unsigned char i=0, j=0, excuse_me = 0; 
char receive_state = R_WAITING;    			// state of the receiver ,  R_WAITING or R_OPERATING
char systemState = S_IDLE;    	    		// state of the system; S_IDLE or S_ACTIVE
char transmitBuffer[SIZE_TM_BUF];         	// holds the bytes to be transmitted
char receiveBuffer[SIZE_RC_BUF]; 			// holds received bytes
char robotSituation = CANSTOP; 				// robot is in center of the cell 
int encoderValue, front, right, rear, left; // variables for encoder responses
int visited = 0; 							// currently visited cell count 
int x = 0, y = 0; 							// using for robot coordinates
short internalSum = 0, robotDegree = 180; 	// robot's location and degree info are kept in these variables
extern char map[4][16]; 					// updated map information is kept in this variable

/**********************************************************************
 * ----------------------- GLOBAL FUNCTIONS ---------------------------
 **********************************************************************/

/* These are the given functions that are in the recitation6. */

void transmitBuffer_push(char *str,unsigned char size) // pushes reverse str to buffer.
{
    excuse_me = 1; //kindly interject transmission, this is atomic.
    i = 0;
    while(i < size)
    {
        transmitBuffer[transmitBuffer_pushPtr] = str[i];
        transmitBuffer_pushPtr = (transmitBuffer_pushPtr+1)%SIZE_TM_BUF;
        i++;
    }
    excuse_me = 0;
    TXSTA1bits.TXEN = 1; //enable transmission.
}

void transmitData()
{
    if(transmitBuffer_popPtr != transmitBuffer_pushPtr && !excuse_me)
    {

        TXREG1 = transmitBuffer[transmitBuffer_popPtr];
        transmitBuffer_popPtr = (transmitBuffer_popPtr+1)%SIZE_TM_BUF;
    }
    else
    {
	TXSTA1bits.TXEN = 0;// disable transmission, nothing to push, or excuse_me.
    }
}

unsigned char receiveBuffer_pop(char *str) //pops str from recieved string, returns the length of the popped string.
{
    j = 0;
    
    while(receiveBuffer[receiveBuffer_popPtr] != '$' && receiveBuffer_popPtr != receiveBuffer_pushPtr)
    {
        receiveBuffer_popPtr = (receiveBuffer_popPtr+1)%SIZE_RC_BUF;
    }

    if (receiveBuffer_popPtr == receiveBuffer_pushPtr) return 0; // ignore garbage

    receiveBuffer_popPtr = (receiveBuffer_popPtr+1)%SIZE_RC_BUF;; //skip $

    while(receiveBuffer[receiveBuffer_popPtr] != ':' && receiveBuffer_popPtr != receiveBuffer_pushPtr)
    {
        str[j] = receiveBuffer[receiveBuffer_popPtr];
        j++;
        receiveBuffer_popPtr = (receiveBuffer_popPtr+1)%SIZE_RC_BUF;
    }

    if (receiveBuffer_popPtr == receiveBuffer_pushPtr) return 0; //ignore garbage, the string did not end with ":".

    receiveBuffer_popPtr = (receiveBuffer_popPtr+1)%SIZE_RC_BUF; //skip ":"

    return j;
}


/* Invoked when receive interrupt occurs; meaning that data is received */
void dataReceived()
{
    unsigned char rxbyte = RCREG1;

    if(receive_state == R_WAITING && rxbyte == '$')
    {
       receiveBuffer[receiveBuffer_pushPtr] = rxbyte;
       receiveBuffer_pushPtr = (receiveBuffer_pushPtr+1)%SIZE_RC_BUF;
       receive_state = R_OPERATING;
    }
    else if(receive_state == R_OPERATING && rxbyte != ':')
    {
       receiveBuffer[receiveBuffer_pushPtr] = rxbyte;
       receiveBuffer_pushPtr = (receiveBuffer_pushPtr+1)%SIZE_RC_BUF;
    }
    else if(receive_state == R_OPERATING && rxbyte == ':')
    {
       receiveBuffer[receiveBuffer_pushPtr] = rxbyte;
       receiveBuffer_pushPtr = (receiveBuffer_pushPtr+1)%SIZE_RC_BUF;
       receive_state = R_WAITING;
    }


}

/* End of File : common.c */

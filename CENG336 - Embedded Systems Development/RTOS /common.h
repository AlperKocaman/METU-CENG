/* 
Yavuz Selim YESILYURT - 2259166
Alper KOCAMAN - 2169589
*/

#ifndef _COMMON_H
#define COMMON_H

#include "device.h"

/***********************************************************************
 * ------------------------ Timer settings -----------------------------
 **********************************************************************/
#define _10MHZ	63320
#define _16MHZ	61768
#define _20MHZ	60768
#define _32MHZ	57768
#define _40MHZ 	55768

/***********************************************************************
 * ----------------------------- Events --------------------------------
 **********************************************************************/
#define ALARM_EVENT       0x80

/***********************************************************************
 * ----------------------------- Task ID -------------------------------
 **********************************************************************/
/* Info about the tasks:
 * TASK0: GAME TASK
 * TASK1: RECEIVE TASK
 * TASK2: LCD TASK
 */
#define GAME_TASK_ID            1 
#define RCV_TASK_ID             2
#define LCD_TASK_ID             3

/* Priorities of the tasks */
/* Lcd task should be preempted by both receive task and game task */
#define RCV_TASK_PRIO   8
#define GAME_TASK_PRIO  8
#define LCD_TASK_PRIO   9

#define GAME_ALARM              0 // for game task
#define RECEIVE_ALARM           1 // for receive task
#define LCD_ALARM               2 // for delay function in the lcd task
#define LCD_ALARM2              3 // periodically wake up lcd task 

/**********************************************************************
 * ----------------------- GLOBAL DEFINITIONS -------------------------
 **********************************************************************/

/* System States */

#define S_IDLE      0		// Simulator idle state
#define S_ACTIVE    1		// Simulator active state

#define R_WAITING      0	// Receiver idle state
#define R_OPERATING    1	// Receiver active state

#define SIZE_TM_BUF 100     // transmitter buffer size is 100     
#define SIZE_RC_BUF 100     // receiver buffer size is 100

/* Robot states */
#define MOVING  0          
#define TURNING_RIGHT 1
#define TURNING_LEFT 2
#define CANSTOP 3
#define STOPPED 4


/**********************************************************************
 * ----------------------- FUNCTION PROTOTYPES ------------------------
 **********************************************************************/
 /* transmits data using serial communication */
void transmitData();
/* Invoked when receive interrupt occurs; meaning that data is received */
void dataReceived();

void transmitBuffer_push(char *str,unsigned char size);

unsigned char receiveBuffer_pop(char *str);

#endif

/* End of File : common.h */

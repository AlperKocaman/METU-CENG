/* Explanations *************************************************************************************************************************************
|
| The Tic-Tac-Toe board has 9 cells. We will assume that the cell numbering is as follows:
|
|   c0 | c1 | c2
|   ------------
|   c3 | c4 | c5
|   ------------
|   c6 | c7 | c8
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR  ( "Alper Kocaman" )  /* Author's name                                   */

#define EMPTY   ( ' '             )  /* Label for empty cells                           */
#define PLAYER1 ( 'X'             )  /* Label for player 1 and cells marked by player 1 */
#define PLAYER2 ( 'O'             )  /* Label for player 2 and cells marked by player 2 */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

char c0 , c1 , c2 , c3 , c4 , c5 , c6 , c7 , c8 ;  /* Cells of the Tic-Tac-Toe board */

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Initializes the global variables. */

void initializeGlobalVariables ( void )
{

  c0 , c1 , c2 , c3 , c4 , c5 , c6 , c7 , c8 = EMPTY;

}

/*=================================================================================================================================================*/

/* Prints a banner including the author name. */

void printBanner ( void )
{
  printf(                                                                                   "\n"          ) ;
  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* Tic-Tac-Toe                                                                 *" "\n"          ) ;
  printf( "* by %-72s *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

/* Prints the current board configuration. */

void printBoard ( void )
{

  printf("Cells                  Board\n");
  printf(".-----------.          .-----------.\n");
  printf("| 0 | 1 | 2 |          | c0| c1| c2|\n");
  printf("| 3 | 4 | 5 |          | c3| c4| c5|\n");
  printf("| 6 | 7 | 8 |          | c6| c7| c8|\n");

  printf("Player %c, enter your next move (0-8) :  \n\n",currentPlayer);

}

/*=================================================================================================================================================*/

/* Gets the next move of "player", and marks it on the board.                     */
/* Loops (and asks again) if the input is not valid, or if the cell is not empty. */

void getNextMove ( char player )
{
  /* TODO */
  /* ...  */
}

/*=================================================================================================================================================*/

/* Checks if one of the players wins the game, or if the board is full and the game ended with a draw. Prints how the game ended. */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                                     */

boolean checkAndPrintGameResult ( void )
{
  /* TODO */
  /* ...  */
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Initializes the global variables.                                                                                                          */
/* Prints banner.                                                                                                                             */
/* Randomly chooses one of the players to start first.                                                                                        */
/* Asks each player to make a move in turn until the game finishes (prints the board configuration each time before a player makes her move). */
/* Prints the game result.                                                                                                                    */
/* Prints a goodbye message.                                                                                                                  */
/* Prints the number of random numbers that were generated during the game play.                                                              */

int main ( void )
{
  int i;

  char currentPlayer = ( ( randomIntegerMinMaxUnBiased( 0 , 1 ) == 0 ) ? PLAYER1 : PLAYER2 ) ;

  initializeGlobalVariables() ;
  printBanner              () ;
  printBoard               () ;

  do
  {
    getNextMove( currentPlayer ) ;
    printBoard (               ) ;

    if   ( currentPlayer == PLAYER1 )  { currentPlayer = PLAYER2 ; }
    else                               { currentPlayer = PLAYER1 ; }
  }
  while ( checkAndPrintGameResult() == FALSE ) ;

  printf( "\nGood game. Have a nice day!\n" ) ;

  printf( "\n%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;

  return 0 ;
}

/***************************************************************************************************************************************************/

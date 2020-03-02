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

int counter ; /* This global variable is added up since it eases to check whether game is finished with draw or not.*/

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Initializes the global variables. */

void initializeGlobalVariables ( void )
{

  c0 = EMPTY;

  c1 = EMPTY;

  c2 = EMPTY;

  c3 = EMPTY;

  c4 = EMPTY;

  c5 = EMPTY;

  c6 = EMPTY;

  c7 = EMPTY;

  c8 = EMPTY;

  counter = 0;

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
  printf("\n");
  printf("    Cells                  Board\n");
  printf(".-----------.          .-----------.\n");
  printf("| 0 | 1 | 2 |          | %c | %c | %c |\n",c0 ,c1 ,c2);
  printf("|-----------|          |-----------|\n");
  printf("| 3 | 4 | 5 |          | %c | %c | %c |\n",c3 ,c4 ,c5);
  printf("|-----------|          |-----------|\n");
  printf("| 6 | 7 | 8 |          | %c | %c | %c |\n",c6 ,c7 ,c8);
  printf("'-----------'          '-----------'\n\n");


}

/*=================================================================================================================================================*/

/* Gets the next move of "player", and marks it on the board.                     */
/* Loops (and asks again) if the input is not valid, or if the cell is not empty. */

void getNextMove ( char player )
{

  int i,input;

  i = -1;

  input = FALSE;

  do {

  printf("Player %c, enter your next move (0-8) : ",player);

  if (   scanf(" %d",&i)  > 10);

  printf("   \n");

  if(i == 0) {

    if(c0 == EMPTY) {

      c0 = player ;

      counter++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

  else if(i == 1) {

    if(c1 == EMPTY) {

      c1 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

  else if(i == 2) {

    if(c2 == EMPTY) {

      c2 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

}

}

  else if(i == 3) {

    if(c3 == EMPTY) {

      c3 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

  else if(i == 4) {

    if(c4 == EMPTY) {

      c4 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

  else if(i == 5) {

    if(c5 == EMPTY) {

      c5 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

  else if(i == 6) {

    if(c6 == EMPTY) {

      c6 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

  else if(i == 7) {

    if(c7 == EMPTY) {

      c7 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

  else if(i == 8) {

    if(c8 == EMPTY) {

      c8 = player ;

      counter ++;

      input = TRUE;

    }

  else {

    printf("Cell is not empty! Please try again.\n\n");

  }

}

else printf("Incorrect input! Please try again.\n\n");

  clearInputBuffer();



}while(input == FALSE);


  return ;

}

/*=================================================================================================================================================*/

/* Checks if one of the players wins the game, or if the board is full and the game ended with a draw. Prints how the game ended. */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                                     */

boolean checkAndPrintGameResult ( void )
{
  if((c0 == c1) && (c1 == c2) && (c0 != EMPTY)) {

    if(c0 == 'X') {

      printf("Player X WINS (top row)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (top row)!\n");

      return TRUE;

    }


  }

  if((c3 == c4) && (c4 == c5)&& (c3 != EMPTY)) {

    if(c3 == 'X') {

      printf("Player X WINS (middle row)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (middle row)!\n");

      return TRUE;

    }


  }

  if((c6 == c7) && (c7 == c8)&& (c6 != EMPTY)) {

    if(c8 == 'X') {

      printf("Player X WINS (bottom row)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (bottom row)!\n");

      return TRUE;

    }


  }

  if((c0 == c3) && (c3 == c6)&& (c0 != EMPTY)) {

    if(c0 == 'X') {

      printf("Player X WINS (left column)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (left column)!\n");

      return TRUE;

    }


  }

  if((c4 == c1) && (c1 == c7)&& (c1 != EMPTY)) {

    if(c1 == 'X') {

      printf("Player X WINS (middle column)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (middle column)!\n");

      return TRUE;

    }


  }

  if((c2 == c5) && (c5 == c8)&& (c2 != EMPTY)) {

    if(c2 == 'X') {

      printf("Player X WINS (right column)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (right column)!\n");

      return TRUE;

    }


  }

  if((c0 == c4) && (c4 == c8)&& (c0 != EMPTY)) {

    if(c0 == 'X') {

      printf("Player X WINS (primary diagonal)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (primary diagonal)!\n");

      return TRUE;

    }


  }

  if((c2 == c4) && (c4 == c6)&& (c2 != EMPTY)) {

    if(c2 == 'X') {

      printf("Player X WINS (secondary diagonal)!\n");

      return TRUE;

    }

    else {

      printf("Player O WINS (secondary diagonal)!\n");

      return TRUE;

    }


  }

  if (counter == 9) {

    printf("DRAW!\n");

    return TRUE;


  }

  return FALSE;


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

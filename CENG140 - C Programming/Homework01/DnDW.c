/* Explanations *************************************************************************************************************************************
|
| - The dungeon consists of a "start" room, an "exit" room, one room with "gold", one or more rooms with "wumpuses", and zero or more empty rooms.
| - "Start" and "exit" rooms are empty.
| - Other rooms can be empty, or can contain only a single entity (either gold, or wumpus). A room cannot contain more than one entities.
| - At the beginning of the game, the player sets the total number of rooms, and also the number of wumpuses.
| - Player starts in room "start".
| - All rooms are magical, and they all have 2 doors.
| - Doors might appear randomly in North, East, South or West directions.
| - Doors lead to randomly selected other rooms.
| - If the player visits the room with the gold, the player grabs the gold.
| - If the player visits a room with a wumpus in it, the wumpus eats the player, and the game finishes.
| - If the player visits the "exit" room, the game finishes. If the player has the gold with her, this is a successful finish.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR       ( "Alper Kocaman" )  /* Author's name                                                                   */

#define MIN_ROOMS    (  2              )  /* Minimum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MAX_ROOMS    (  8              )  /* Maximum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MIN_WUMPUSES (  1              )  /* Minimum number of wumpuses in the dungeon                                       */
#define MAX_WUMPUSES (  4              )  /* Maximum number of wumpuses in the dungeon                                       */

#define START        ( 'S'             )  /* Label for the start room                                                        */
#define EXIT         ( 'X'             )  /* Label for the exit room                                                         */
#define GOLD         ( 'G'             )  /* Label for the single room containing the gold                                   */
#define WUMPUS       ( 'W'             )  /* Label for room(s) containing a wumpus                                           */
#define EMPTY        ( 'E'             )  /* Label for empty room(s)                                                         */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

int     numberOfMagicalRooms                            ;
int     numberOfWumpuses                                ;
int     currentRoomNo                                   ;
boolean playerFoundGold                                 ;
char    r0 , r1 , r2 , r3 , r4 , r5 , r6 , r7 , r8 , r9 ; /* r0 is start room, r1 is exit room, others are magical rooms (at most 8 magical rooms) */

/***************************************************************************************************************************************************/




/* Helper (Minor) Functions ************************************************************************************************************************/

/* The input is the room number, and the return value is the label for the room. */

char getRoomInformation ( int roomNo )
{
  switch ( roomNo )
  {
    default :
    case 0  : return r0 ;
    case 1  : return r1 ;
    case 2  : return r2 ;
    case 3  : return r3 ;
    case 4  : return r4 ;
    case 5  : return r5 ;
    case 6  : return r6 ;
    case 7  : return r7 ;
    case 8  : return r8 ;
    case 9  : return r9 ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room label. The function prints out the information associated with the label. */

void printRoomInformation1 ( char room )
{
  switch ( room )
  {
    case START  : printf( "START"  ) ;  break ;
    case EXIT   : printf( "EXIT"   ) ;  break ;
    case GOLD   : printf( "GOLD"   ) ;  break ;
    case WUMPUS : printf( "WUMPUS" ) ;  break ;
    case EMPTY  : printf( "EMPTY"  ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room number. The function prints out the information associated with the room. */

void printRoomInformation2 ( int roomNo )
{
  switch ( roomNo )
  {
    case 0 : printRoomInformation1( r0 ) ;  break ;
    case 1 : printRoomInformation1( r1 ) ;  break ;
    case 2 : printRoomInformation1( r2 ) ;  break ;
    case 3 : printRoomInformation1( r3 ) ;  break ;
    case 4 : printRoomInformation1( r4 ) ;  break ;
    case 5 : printRoomInformation1( r5 ) ;  break ;
    case 6 : printRoomInformation1( r6 ) ;  break ;
    case 7 : printRoomInformation1( r7 ) ;  break ;
    case 8 : printRoomInformation1( r8 ) ;  break ;
    case 9 : printRoomInformation1( r9 ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the direction. The function prints out the direction as a word, as an acronym and also displays an arrowhead. */

void printDirection ( int direction )
{
  switch ( direction )
  {
    case 0 : printf( "NORTH (N) ^" ) ;  break ;
    case 1 : printf( "EAST (E) >"  ) ;  break ;
    case 2 : printf( "SOUTH (S) v" ) ;  break ;
    case 3 : printf( "WEST (W) <"  ) ;  break ;
  }
}

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Prints a banner including the author name. */

void printBanner ( void )
{
  printf(                                                                                   "\n"          ) ;
  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* Dungeons and Dragons with Wumpuses                                          *"  "\n"          ) ;
  printf( "* by %-72s *" "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;

}

/*=================================================================================================================================================*/

/* Initializes all global variables.                                                                                    */
/* The number of magical rooms and the number of wumpuses are set by the player as part of the configuration process.   */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */

void configureWorld ( void )
{
  currentRoomNo = 0;

  playerFoundGold = FALSE;

  r0 = START;

  r1 = EXIT;

  r2 = GOLD;

  r3 = WUMPUS ;

  r4 = r5 = r6 = r7 = r8 = r9 = EMPTY ;

  printf(                                                                                   "\n"          ) ;
  printf("Let's configure the DnDW World first!\n");

  do {

    printf("Enter number of magical rooms [2,8] : ");

    if (  scanf(" %d", &numberOfMagicalRooms ) > 10 );

    if ((numberOfMagicalRooms>=MIN_ROOMS) && (numberOfMagicalRooms<=MAX_ROOMS))

      break;

    printf("Incorrect input! Please try again.\n");

    clearInputBuffer();

  }while(TRUE);

  do {

    printf("Enter number of wumpuses [1,4]      : ");

    if (  scanf(" %d", &numberOfWumpuses) > 10 );

    if ((numberOfWumpuses >= MIN_WUMPUSES) && (numberOfWumpuses <= MAX_WUMPUSES) && (numberOfWumpuses < numberOfMagicalRooms))

      break;

    printf("Incorrect input! Please try again.\n");

    clearInputBuffer();

  }while(TRUE);

  switch (numberOfWumpuses) {
    case 4: r6 = WUMPUS;
    case 3: r5 = WUMPUS;
    case 2: r4 = WUMPUS;

  }

  printf("Configuration is finished. Good luck with the game play!\n");

}

/*=================================================================================================================================================*/

/* Prints the configured world. */

void printWorld ( void )
{
  int i=0;

  printf(                                                                                   "\n"          ) ;
  printf("DnD World:\n");
  printf("----------\n");
  printf("Room 0 : START\n");
  printf("Room 1 : EXIT\n");
  printf("Room 2 : GOLD\n");

  for(; i < numberOfWumpuses ;i++) {

    printf("Room %d : WUMPUS\n",i+3);
  }

  for(;i < numberOfMagicalRooms-1 ;i++) {

    printf("Room %d : EMPTY\n",i+3);

  }

}

/*=================================================================================================================================================*/

/* Prints the current room information and the doors of the current room.                                               */
/* Gets player's door choice as one of 'N', 'E', 'S', 'W' (small letters should also be accepted).                      */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */
/* Prints where the doors were actually opening to.                                                                     */
/* Updates current room number.                                                                                         */
/* If the current room contains gold, lets the player know that she now has gold in her posession.                      */

void getNextMove ( void )
{
    int direction1,direction2,door1_to_room,door2_to_room;
    char directionchoose1big,directionchoose1small,directionchoose2big,directionchoose2small,preferred  ;

    directionchoose1big = directionchoose1small = directionchoose2big = directionchoose2small = preferred = ' ';

    printf("\nYou are in room %d\n", currentRoomNo);
    printf("Room information : ");
    printRoomInformation2(currentRoomNo);
    printf(" \n");
    direction1 = randomIntegerMaxUnBiased(3);
    direction2 = randomIntegerMinMaxUnBiasedExcept1(0,3,direction1);

    printf("There is a door to your ");
    printDirection(direction1);
    printf(" \n");
    printf("And, there is another door to your ");
    printDirection(direction2);
    printf(" \n");

    printf("Which one will you choose? : ");

    if (direction1 == 0) {

      directionchoose1big = 'N' ;

      directionchoose1small = 'n';

}

    else if (direction1 == 1) {

      directionchoose1big = 'E' ;

      directionchoose1small = 'e';

}

    else if (direction1 == 2) {

      directionchoose1big = 'S' ;

      directionchoose1small = 's';

}

    else if (direction1 == 3) {

      directionchoose1big = 'W' ;

      directionchoose1small = 'w';

}

    if (direction2 == 0) {

      directionchoose2big = 'N' ;

      directionchoose2small = 'n';

}

    else if (direction2 == 1) {

      directionchoose2big = 'E' ;

      directionchoose2small = 'e';

}

    else if (direction2 == 2) {

      directionchoose2big = 'S' ;

      directionchoose2small = 's';

}

    else if (direction2 == 3) {

      directionchoose2big = 'W' ;

      directionchoose2small = 'w';

}

    do {

      if(   scanf(" %c",&preferred)  >  10 );

      if ((preferred == directionchoose1big) || (preferred == directionchoose1small) || (preferred == directionchoose2big) || (preferred == directionchoose2small)) {

        break;
}

      printf("Incorrect input! Please try again : ");

      clearInputBuffer();

    }while (TRUE) ;

     door1_to_room = randomIntegerMinMaxUnBiasedExcept1(0,numberOfMagicalRooms+1,currentRoomNo);
     door2_to_room = randomIntegerMinMaxUnBiasedExcept2(0,numberOfMagicalRooms+1,door1_to_room,currentRoomNo);

    printf("Room to your ");
    printDirection(direction1);
    printf(" was Room %d",door1_to_room);
    printf(" \n");

    printf("Room to your ");
    printDirection(direction2);
    printf(" was Room %d",door2_to_room);


    if ((preferred == directionchoose1big) || (preferred == directionchoose1small))

      currentRoomNo = door1_to_room;

    else currentRoomNo = door2_to_room;

    if (currentRoomNo == 2) {
    	
    	if(playerFoundGold == FALSE) {
		
      printf("\nYou have GOLD now!");

      playerFoundGold = TRUE;

	}
	
    }

    printf(" \n");
}

/*=================================================================================================================================================*/

/* Checks if the current room that the player is in is the exit room.                                           */
/* If so, checks if the player already has the gold or not, and prints out an appropriate message in each case. */
/* Also checks if the player is in a room with a wumpus.                                                        */
/* If so, informs the player about the unhappy ending of the game.                                              */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                   */

boolean checkAndPrintGameResult ( void )
{
  if (getRoomInformation(currentRoomNo) == WUMPUS) {

    printf("Wumpus is full, and you are in heaven! What a pity!\n");

    return TRUE;

  }

  else if (getRoomInformation(currentRoomNo) == EXIT) {

    if (playerFoundGold == TRUE) {

      printf("You are safely out of the dungeon with the GOLD! Congratulations!\n");

    }

    else {

      printf("You are safely out of the dungeon, but you did not find the GOLD! Better luck next time!\n");

    }
    return TRUE;

  }

  return FALSE;
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Prints banner.                                                                */
/* Configures the dungeon world.                                                 */
/* Prints the configured world.                                                  */
/* Asks the player to make a move until the game finishes .                      */
/* Prints the game result.                                                       */
/* Prints a goodbye message.                                                     */
/* Prints the number of random numbers that were generated during the game play. */

int main ( void )
{
  printBanner();
  configureWorld();
  printWorld();

  while(checkAndPrintGameResult() == FALSE) {

    getNextMove();

  }

  printf( "\nGood game. Have a nice day!\n" ) ;

  printf( "\n%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;

  return 0;
}

/***************************************************************************************************************************************************/

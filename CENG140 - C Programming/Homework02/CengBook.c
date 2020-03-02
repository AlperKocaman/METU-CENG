/* Explanations *************************************************************************************************************************************
|
| This file implements CengBook, which is a realistic simulation of a mini social-media application.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"
#include "Queue.h" /* I added up since it is needed to use some utility functions.*/ 

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************************************************************/




/* Macro Definitions *******************************************************************************************************************************/

#define AUTHOR ( "Alper KOCAMAN" )  /* Author's name */  /* TODO: Replace with your name */

/***************************************************************************************************************************************************/




/* Global Variable Definitions *********************************************************************************************************************/

BookPtr bookPtr ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#if   defined(_WIN16) || defined(_WIN32) || defined(_WIN64)

  char operatingSystem[] = "Windows" ;  /* This is a Windows environment.                            */

#elif defined(__linux__)

  char operatingSystem[] = "Linux"   ;  /* This is a Linux environment (any GNU/Linux distribution). */

#elif defined(__APPLE__)

  char operatingSystem[] = "MacOSX"  ;  /* This is a Mac OS X environment.                           */

#endif

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

void printUsage ( String applicationName )
{
  NL ;

  printf( "Usage: %s <MaxNumberOfUsers> <MaxUserNameLength> <MaxNumberOfFriendsPerUser>\n\n" , applicationName ) ;
}

/*=================================================================================================================================================*/

void printBanner ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* CengBook                                                                    *" "\n"          ) ;
  printf( "* by %-72s *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

void printMenu ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n" ) ;
  printf( "Help                       : Print this menu"                                    "\n" ) ;
  printf( "List                       : List all users"                                     "\n" ) ;
  printf( "Plot                       : Create a plot of CengBook (requires GraphViz)"      "\n" ) ;
  printf( "Quit                       : Exit application"                                   "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Register   <user>          : Create a new user and add it to CengBook"           "\n" ) ;
  printf( "Delete     <user>          : Delete user from CengBook"                          "\n" ) ;
  printf( "Find       <user>          : Search CengBook for user, display user information" "\n" ) ;
  printf( "Connect    <user1> <user2> : Add a connection from user1 to user2"               "\n" ) ;
  printf( "Disconnect <user1> <user2> : Remove connection from user1 to user2"              "\n" ) ;
  printf( "Path       <user1> <user2> : Find shortest path from user1 to user2"             "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Sort <abc|pop> <asc|desc>  : Sort all users (alphabetically or by popularity)"   "\n" ) ;
  printf( "*******************************************************************************" "\n" ) ;
  printf( "************************************BONUS**************************************" "\n" ) ;
  printf( "Recommend   <user>          : Recommend  new friends to an user "                "\n" ) ;
  printf( "*******************************************************************************" "\n" ) ;
}

/*=================================================================================================================================================*/

void commandHelp ( void )
{
    printMenu() ;
}

/*=================================================================================================================================================*/

void commandList ( void )
{
  if( bookPtr->numberOfUsers == 0 ) { NL ; I2 ; printf("CengBook is empty\n");}

  else{

    int i;

    for(i=0; i < bookPtr->numberOfUsers ;i++){

    	NL ; I2 ;

    	printf("%-16s: %d Follower(s) , %d Friend(s)",bookPtr->userPointers[i]->name,bookPtr->userPointers[i]->numberOfFollowers,bookPtr->userPointers[i]->numberOfFriends);


    }

    NL ;
  }

}

/*=================================================================================================================================================*/

void commandPlot ( void )
{
  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  UserPtr   userPtr             , friendPtr              ;
  int       userIndex           , friendIndex            ;
  String    runDotSystemCommand , openImageSystemCommand ;

  FILE    * file = fopen( "CengBook.dot" , "w" )         ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "digraph CengBook"                                                       "\n"                            ) ;
  fprintf( file , "{"                                                                      "\n"                            ) ;
  fprintf( file , "  graph [label=\"CengBook\\nNumber of users = %d\" , labelloc=t] ;"     "\n\n" , bookPtr->numberOfUsers ) ;
  fprintf( file , "  node  [shape=ellipse , fontcolor=black , color=red , penwidth=2.0] ;" "\n\n"                          ) ;
  fprintf( file , "  edge  [color=blue , penwidth=2.0] ;"                                  "\n\n"                          ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    fprintf( file , "  %s [label=\"%s\\n%d Friend(s)\\n%d Follower(s)\"] ;\n" ,
             userPtr->name                                                    ,
             userPtr->name                                                    ,
             userPtr->numberOfFriends                                         ,
             userPtr->numberOfFollowers                                       ) ;
  }

  if ( bookPtr->numberOfUsers > 0 )  { fprintf( file , "\n" ) ; }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    for ( friendIndex = 0 ; friendIndex < userPtr->numberOfFriends ; friendIndex++ )
    {
      friendPtr = userPtr->friendPointers[ friendIndex ] ;

      fprintf( file , "  %s -> %s ;\n" , userPtr->name , friendPtr->name ) ;
    }
  }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "}\n" ) ;
  fclose ( file         ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  if ( strcmp( operatingSystem , "Windows" ) == 0 )
  {
    runDotSystemCommand    = "CMD /C dot -Tgif CengBook.dot -o CengBook.gif" ;
    openImageSystemCommand = "CMD /C START CengBook.gif"                     ;
  }
  else  /* Assumption: Linux */
  {
    runDotSystemCommand    = "dot -Tgif CengBook.dot -o CengBook.gif"        ;
    openImageSystemCommand = "xdg-open CengBook.gif &"                       ;
  }

  if ( system( runDotSystemCommand    ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */
  if ( system( openImageSystemCommand ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */

  NL ;  I2 ;  printf( "Plot prepared\n" ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/
}

/*=================================================================================================================================================*/

void commandQuit ( void )
{
  	NL ; I2 ;

	printf("Have a nice day\n"); NL ;

	exit(0);
}

/*=================================================================================================================================================*/

void commandRegister ( String userName )
{
	if( strlen(userName) > getMaxUserNameLength() ) {NL ; I2 ; printf("User name is longer than %d characters!\n", getMaxUserNameLength() ) ; return ;}

  else if( getUserPtrByName( bookPtr , userName ) != NULL ) { NL ; I2 ; printf ("User '%s' already registered!", userName ) ; NL ; return; }

  else if(bookPtr->numberOfUsers == getMaxNumberOfUsers() ) {  NL ; I2 ; printf ("CengBook is full, cannot register any new users!") ; NL ; return ; }

  else {

		bookPtr->userPointers[bookPtr->numberOfUsers] = allocateUser( userName);

		bookPtr->numberOfUsers ++ ;

		NL ; I2 ; printf("User '%s' registered successfully", userName); NL ;
	}
}

/*=================================================================================================================================================*/

void commandDelete ( String userName )
{
	int deleted_index;

	UserPtr deleted_user, temp;

  temp = ( UserPtr ) malloc ( sizeof ( User ) );

  deleted_user = getUserPtrByName( bookPtr , userName );

  if(deleted_user == NULL)  {  NL ; I2 ; printf("User '%s' not found in CengBook!", userName); NL ; free( deleted_user ) ; free( temp ) ; return ; }

	else {

    int i=0 , j=0; NL ;

    while( i < deleted_user->numberOfFollowers ) {

        if( isConnected ( bookPtr->userPointers[j] , deleted_user ) ) {

            removeConnection ( bookPtr->userPointers[j] , deleted_user ) ;

            I2 ; printf("User '%s' is removed from friends of user '%s'", userName , bookPtr->userPointers[j]->name ); NL ;
        }

      j++;

    }

    i = 0 ; 

    for(i=0 ; i < deleted_user->numberOfFriends ; i++) {

      deleted_user->friendPointers[i]->numberOfFollowers --;

      I2 ; printf("User '%s' is discounted from followers of user '%s'", userName , deleted_user->friendPointers[i]->name) ; NL ;

    }

		deleted_index = getUserIndexByPtr ( bookPtr , deleted_user ) ;

		deallocateUser( deleted_user );

		for ( ; deleted_index < (bookPtr->numberOfUsers -1) ; deleted_index++ ) {

			temp = bookPtr->userPointers[deleted_index +1] ;

			bookPtr->userPointers[deleted_index] =	temp;
		}
    bookPtr->numberOfUsers --;

		bookPtr->userPointers[bookPtr->numberOfUsers] = NULL;
	}

	I2 ; printf("User '%s' is deleted from CengBook", userName);  NL; return ;
}

/*=================================================================================================================================================*/

void commandFind ( String userName )
{
  NL;

  if( getUserPtrByName( bookPtr , userName ) )

    printUser ( getUserPtrByName( bookPtr , userName ) );

  else { I2 ; printf("User '%s' not found in CengBook!", userName ) ; NL ; }

  return ;
}

/*=================================================================================================================================================*/

void commandConnect ( String userName1 , String userName2 )
{
    UserPtr friend_increase , follower_increase;

    friend_increase   = getUserPtrByName( bookPtr , userName1 );

    follower_increase = getUserPtrByName( bookPtr , userName2 );

    if( ( !friend_increase ) || ( !follower_increase ) ) {
    if ( !friend_increase ) {

      NL ; I2 ;

      printf("User '%s' not found in CengBook!", userName1 ); 

    }

    if ( !follower_increase ) {

      NL ; I2 ;

      printf("User '%s' not found in CengBook!", userName2 ); 

      }

      NL;


    return ;
  }

  	if( friend_increase == follower_increase) {

        NL ; I2 ; printf("Connection to self is not allowed!") ; NL ; return ;
    }

    if( friend_increase->numberOfFriends == getMaxNumberOfFriendsPerUser () ) {

       NL ; I2 ; printf("Friend capacity of user '%s' is full!", userName1) ; NL ; return ;
    }

    if( isConnected ( friend_increase , follower_increase ) ) {

        NL ; I2 ; printf("User '%s' is already connected to user '%s'!", userName1 , userName2 ) ; NL ; return ;
    }

    friend_increase->friendPointers[friend_increase->numberOfFriends ++] = follower_increase;

    follower_increase->numberOfFollowers ++;

    NL ; I2 ; printf("User '%s' successfully connected to user '%s'", userName1, userName2 ) ; NL ;
}

/*=================================================================================================================================================*/

void commandDisconnect ( String userName1 , String userName2 )
{
    int if_terminate = 0 ;

  	UserPtr account1 = malloc(sizeof(User));

    UserPtr account2 = malloc(sizeof(User));

  	account1 = getUserPtrByName( bookPtr , userName1 );

  	if ( account1 == NULL ) { NL ; I2 ; printf("User '%s' not found in CengBook!", userName1 ); if_terminate = 1 ; }

    account2 = getUserPtrByName( bookPtr , userName2 );

    if ( account2 == NULL ) { NL ; I2 ; printf("User '%s' not found in CengBook!", userName2 ); if_terminate=1 ; }

    if( if_terminate == 1) { NL ; return ;}

    if( account1 == account2 ) { NL ; I2 ; printf("Disconnecting from self is not allowed!"); NL; return ;}
  
	if( isConnected ( account1 , account2 ) ) {

		removeConnection ( account1 , account2 );

		NL ; I2 ; printf("User '%s' successfully disconnected from user '%s'", userName1 , userName2 ) ; NL ; return ;
	}

	else {

		NL ; I2 ; printf("User '%s' and user '%s' are not connected!", userName1 , userName2 ) ; NL ; return ;
	}
}

/*=================================================================================================================================================*/

void commandPath ( String userName1 , String userName2 )
{       
    int if_terminate = 0 ;

  	UserPtr account1 = malloc(sizeof(User));

    UserPtr account2 = malloc(sizeof(User));

  	UserPtrArray path = malloc( bookPtr->numberOfUsers * sizeof(char *) );

  	account1 = getUserPtrByName( bookPtr , userName1 );

  	if ( account1 == NULL ) { NL ; I2 ; printf("User '%s' not found in CengBook!", userName1 );  if_terminate = 1 ; }

    account2 = getUserPtrByName( bookPtr , userName2 );

    if ( account2 == NULL ) { NL ; I2 ; printf("User '%s' not found in CengBook!", userName2 );  if_terminate = 1 ;}

    if( if_terminate == 1) { NL ; return ;}

    if( account1 == account2) { NL ; I2 ; printf("Path to self queried!") ; NL; return ;}

    if( !( path = shortestPath ( bookPtr , account1 , account2 ) ) ) { NL ; I2 ; 

    	printf("There is no path from user '%s' to user '%s'", userName1 , userName2 ); NL; return ;}

    else { 

    	int i=0; 

    	NL ; I2 ;

		printf("'%s'", path[i]->name );    	 

    	for(i = 1; path[i] != '\0' ; i++  ) printf(" -> '%s'", path[i]->name ) ; 

    	NL ; return ;
	}	   
}

/*=================================================================================================================================================*/

void commandRecommend ( String userName ){ /* This is a bonus implementation*/

	UserPtr user = malloc(sizeof(User));

	user = getUserPtrByName( bookPtr , userName );

	if(user == NULL)  {  NL ; I2 ; printf("User '%s' not found in CengBook!", userName); NL ; free( user ) ;  return ; }

	else {

    int i=0 , j=0; NL ;

    while( i < user->numberOfFollowers ) {

        if( isConnected ( bookPtr->userPointers[j] , user ) ) {

        i++ ;	I2 ; 

        printf("User '%s' is recommended to user '%s' since User '%s' is one of the follower." , bookPtr->userPointers[j]->name , userName , bookPtr->userPointers[j]->name  ); 

        NL ;
        
        }

      j++;

    }

	}

}

/*=================================================================================================================================================*/

void commandSort ( String criterion , String order )	
{
	boolean ascending = 0, if_terminate = 0 ,abc_or_pop = 0;

	ComparatorFunctionPointer compareFunctionPtr;

	if ( strcmp(criterion , "abc") == 0 ) { compareFunctionPtr = &compareByName ; abc_or_pop = 1 ; }

	else if ( strcmp(criterion , "pop") == 0) { compareFunctionPtr = &compareByPopularity ;}

	else { NL ; I2 ; printf("Invalid sort criterion '%s'!", criterion ) ; if_terminate = 1 ; }

	if( strcmp(order , "asc" ) == 0) {ascending = 1 ;}

	else if( strcmp(order , "desc" ) == 0 ) {ascending = 0 ;} 

	else { NL ; I2 ; printf("Invalid sort order '%s'!", order ) ;  if_terminate = 1 ; }

	if ( if_terminate == 1) { NL ; return ; }		

  	else {

  	String str1 , str2 ;

	str1 = ( String ) malloc ( 15 * sizeof(char ) );

	str2 = ( String ) malloc ( 12 * sizeof(char ) );	

  	sortBook ( bookPtr , compareFunctionPtr , ascending ) ; 

  	if( abc_or_pop == 1 ) strcpy(str1 , "alphabetically" ) ;

  	else  strcpy(str1 , "by popularity" ) ;

  	if( ascending == 1) str2 = strcpy( str2 , "ascending" ) ;

  	else str2 = strcpy( str2 , "descending" ) ;

  	NL ; I2 ; printf("CengBook sorted '%s' in '%s' order", str1 , str2 ); NL ; return ; 

	}
}

/*=================================================================================================================================================*/

void processInput ( String input )
{
  int         i                                                    ;
  int         numberOfTokens = 0                                   ;
  StringArray tokens         = tokenize( input , &numberOfTokens ) ;
  String      command                                              ;

  if ( numberOfTokens < 1 )  { return ; }

  command = tokens[0] ;

  for ( i = 0 ; i < strlen( command ) ; i++ )  { if ( ( command[i] >= 'A' ) && ( command[i] <= 'Z' ) )  { command[i] += 'a' - 'A' ; } }

  if      ( strcmp( command , "help"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandHelp      (                       ) ;  return ; } }
  else if ( strcmp( command , "list"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandList      (                       ) ;  return ; } }
  else if ( strcmp( command , "plot"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandPlot      (                       ) ;  return ; } }
  else if ( strcmp( command , "quit"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandQuit      (                       ) ;  return ; } }
  else if ( strcmp( command , "register"   ) == 0 )  { if ( numberOfTokens == 2 ) { commandRegister  ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "delete"     ) == 0 )  { if ( numberOfTokens == 2 ) { commandDelete    ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "find"       ) == 0 )  { if ( numberOfTokens == 2 ) { commandFind      ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "connect"    ) == 0 )  { if ( numberOfTokens == 3 ) { commandConnect   ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "disconnect" ) == 0 )  { if ( numberOfTokens == 3 ) { commandDisconnect( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "path"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandPath      ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "sort"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandSort      ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "recommend"   ) == 0 )  { if ( numberOfTokens == 2 ) { commandRecommend  ( tokens[1]             ) ;  return ; } }
  else                                               { NL ;  I2 ;  printf( "Invalid command!\n" ) ;                               return ;   }


  /* If we reach here, the user must have provided incorrect number of arguments to a valid command */

  command[0] += 'A' - 'a' ;

  NL ;  I2 ;  printf( "Incorrect number of arguments provided for the command '%s'!\n" , command ) ;
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

int main ( int argc , char * argv[] )
{
  char input [ MAX_INPUT_LENGTH ] ;

  if ( argc < 4 )  { printUsage( argv[0] ) ;  return 0 ; }

  configureCengBook( /* maxNumberOfUsers          */ atoi( argv[1] ) ,
                     /* maxUserNameLength         */ atoi( argv[2] ) ,
                     /* maxNumberOfFriendsPerUser */ atoi( argv[3] ) ) ;

  bookPtr = allocateBook() ;

  if ( bookPtr == NULL )  { NL ;  printf( "Error: Cannot allocate memory to store CengBook! Exiting!\n\n" ) ;  exit( 0 ) ; }

  printBanner() ;
  printMenu  () ;

  while ( TRUE )
  {
    NL                        ;  /* New line     */
    printf( "[CENGBOOK] > " ) ;  /* Print prompt */

    if ( fgets( input , MAX_INPUT_LENGTH , stdin ) == NULL )  /* Read input line, 'fgets' is safer than 'gets'. */
    {
      /* In the following two lines, the "if" statements surrounding the "freopen" function calls are used to eliminate warnings. */

      if   ( strcmp( operatingSystem , "Windows" ) == 0 )  { if ( freopen( "CON"      , "r" , stdin ) == NULL ) ; }
      else /* Assumption:               Linux          */  { if ( freopen( "/dev/tty" , "r" , stdin ) == NULL ) ; }

      continue ;
    }

    processInput( input ) ;  /* Tokenize and process the input command */
  }

  return 0 ;
}

/***************************************************************************************************************************************************/

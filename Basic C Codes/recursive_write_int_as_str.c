//This program takes an integer and writes it as a string.

#include <stdio.h>

int helper ( int real_i , int i , int counter ) ;

int  printer (int real_i, int i, int counter ) {

	if (i < 10) {

		printf("%d ", i);

		real_i = helper (real_i , i ,counter);

		if( real_i == 0)

			return 0;

		return printer( real_i , real_i , 0 );

	}

	else return printer( real_i , i/10 , counter +1) ;

}

// Below function helps to find 10'th power of most important digit and returns the substracted value.

int helper ( int real_i , int i , int counter ) {

	if (counter != 0)

		return helper( real_i , i*10 , counter -1);

	return (real_i - i) ;

}

int main ( void ) {

	int i;

	scanf(" %d",&i) ;

	printer( i , i , 0) ;

	return 0 ; 

}
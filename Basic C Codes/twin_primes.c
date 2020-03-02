//This program find all consecutive primes.

#include <stdio.h>
#include <math.h> 

//Below function checks whether the given integer is prime or not.

int check_prime( int prime) {

	int i;

	double sroot ;

	sroot = sqrt(prime);

	for ( i = 2 ; i <= (int)sroot ; i++) {

		if (prime % i == 0)

			break ;

	}

	if (i > sroot ) return 1;

	return 0;

}

int main (void) {

	int i , upbound = 0;

	scanf(" %d", &upbound);

	for( i =3; i <= upbound ; i+=2) {

		if(check_prime(i))

			if(check_prime(i+2))

				printf("%d %d \n", i, i+2);

	}

	return 0 ;

}
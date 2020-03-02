#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char const *argv[])
{ 

	if( (argc != 3) && (argc != 4) ) {

		printf("Call with N value\na mapper_proc\nan optional[reduce_proc]\nEXITING\n");

		exit(1) ;
	}

	int i = 0 , j = 0 , k= 0 , return_pid = 0 ;

	char c[12] ;

	char message[1024] ;

	int N = atoi(argv[1]) ;

	if(N == 3) {

	int pipes[N][2] ;

	for(i=0 ; i < N ; i++){

		if(pipe ( pipes[i] ) < 0 ) {printf("Pipe creation error!\n") ; exit(1) ; }
	}

	for(i=0 ; i < N ; i++){

		return_pid = fork() ;

		if( return_pid < 0 ) {printf("Fork process error!\n") ; exit(1) ; }

		else if( return_pid == 0 ) {

			for(j=0 ; j < N ; j++)
				close(pipes[j][1]);

			dup2(pipes[i][0],0);
				
			for(j=0 ; j < N ; j++)	
				close(pipes[j][0]);

			sprintf(c,"%d",i) ;
			
			execl(argv[2],argv[2],i,(char *)NULL) ;
			
			exit(0) ;
			
		}

	}

	for(j=0 ; j < N ; j++)
			
		close(pipes[j][0]);

	j = 0 ;

	while(fgets( message , 1024 , stdin ) != NULL) {
		
		write(pipes[j][1] , message , strlen(message) );

		j++ ;

		if( j == N) j = 0 ;
	}

	for(j=0 ; j < N ; j++){

		close(pipes[j][1]) ;
	}

	for(j=0 ; j < N ; j++)
		
		wait(NULL) ;

	}

	else{

		int pipes[N][2] ;
		int pipes2[N][2] ;

	for(i=0 ; i < N ; i++){

		if(pipe ( pipes[i] ) < 0 ) {printf("Pipe creation error!\n") ; exit(1) ; }
		if(pipe ( pipes2[i] ) < 0 ) {printf("Pipe creation error!\n") ; exit(1) ; }
	}

	for(i=0 ; i < N ; i++){

		return_pid = fork() ;

		if( return_pid < 0 ) {printf("Fork process error!\n") ; exit(1) ; }

		else if( return_pid == 0 ) {

			for(j=0 ; j < N ; j++)
				close(pipes[j][1]);

			dup2(pipes[i][0],0);
				
			for(j=0 ; j < N ; j++)	
				close(pipes[j][0]);

			sprintf(c,"%d",i) ;
			
			execl(argv[2],argv[2],c,(char *)NULL) ;
			
			exit(0) ;
			
		}

	}

	for(j=0 ; j < N ; j++)
			
		close(pipes[j][0]);

	j = 0 ;

	while(fgets( message , 1024 , stdin ) != NULL) {
		
		write(pipes[j][1] , message , strlen(message) );

		j++ ;

		if( j == N) j = 0 ;
	}

	for(j=0 ; j < N ; j++){

		close(pipes[j][1]) ;
	}

	for(j=0 ; j < N ; j++)
		
		wait(NULL) ;

	}

	return 0;


}
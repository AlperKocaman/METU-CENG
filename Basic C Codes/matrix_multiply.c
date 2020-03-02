#include <stdio.h>

/*This function takes 2 matrices, multiply them and prints the multiplicated matrix.*/

void read_matrix( int matrix [][10] , int , int );
void print_matrix(int matrix [][10], int ,int );
void  multiply( int matrix1 [][10], int row1, int col1,  
				int matrix2[][10], int row2, int col2 ) ;

int main ( void ) {
	
	int row1,col1,row2,col2;
	
	int matrix1[10][10] , 
		matrix2[10][10] ;
	
	do{
	
	printf("Enter rows and columns for matrix 1!!\n");
	
	scanf("%d %d", &row1, &col1);
	
	printf("Enter rows and columns for matrix 2!!\n"); 
	
	scanf("%d %d", &row2, &col2);

	} while(col1 != row2);
	
	read_matrix( matrix1 , row1, col1);
	read_matrix( matrix2 , row2, col2);
	
	printf("This is matrix 1:\n");
	print_matrix( matrix1 , row1, col1);
	
	printf("This is matrix 2:\n");
	print_matrix( matrix2 , row2, col2);
	
	multiply( matrix1 , row1 , col1 , matrix2 , row2 , col2);
	
return 0;
	
}

void read_matrix( int matrix [][10], int row ,int column) {
	
	int i , j;
	
	for (i = 0; i < row ; i++) {
		
		for (j = 0 ; j < column ; j++){
			
			scanf("%d",&matrix[i][j]);
			
		}
	}
	
	
}

void  multiply( int matrix1 [][10], int row1, int col1,  

				int matrix2[][10], int row2, int col2 )  {
	
	int i,j,k,par_res = 0;
		
	int result [row1][col2] ;
					
	for (i = 0; i <row1 ;i++) {
				
		for(j = 0; j < col2 ; j++) {
			
			par_res = 0;
		
			for(k = 0 ; k < row2 ; k++) {
			
				par_res += matrix1[i][k]*matrix2[k][j] ; 
			
			}
			printf("i = %d , j = %d\n",i , j);
			printf("result = %d\n",par_res );
			result[i][j] = par_res ;
			printf("In matrix value = %d\n",result[i][j]);
		
		}
					
	}
	printf("This is multiplied matrix\n");
	print_matrix( result , row1 , col2);
}
				
void print_matrix( int matrix[][10] , int row ,int column) {
	
	int i , j;
	
	for (i = 0; i < row ; i++) {
		
		for (j = 0 ; j < column ; j++){
			
			printf(" %d",matrix[i][j]);
			
		}
		printf(" \n");
	}		
	
}

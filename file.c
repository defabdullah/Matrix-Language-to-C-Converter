#include <stdio.h>
#include <string.h>
#include <ctype.h>


void printsep(){ 
	printf("----------\n"); 
}
double scalarMultiplication(double num1,double num2){
	return num1*num2;
}
double **scalarMatrixMultiplication(double scalar, double **matrix, int row, int column){
	double **newMatrix;
	newMatrix=(double**)calloc(column,sizeof(double*));
	for(int i=0;i<column;i++){
		newMatrix[i]=(double*)calloc(row,sizeof(double));
	}

	for(int i=0;i<column;i++){
		for(int j=0;j<row;j++){
			newMatrix[i][j]=(scalar*matrix[i][j]);
		}
	}

	return newMatrix;
}

void printScalar(double value){
	if( (int) value ==value){
		printf("%d",(int) value);
	}else{
		printf("%0.7f", value);
	} 
}

int main(){

int i,j;
for (i=2;i<58;i+=8){
	for(j=1;j<42;j+=3){
	double A[4][4] ;
	double count ;
	double incr ;
	double B[4][1] ;
	double i ;
	double j ;
}
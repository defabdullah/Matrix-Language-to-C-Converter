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

	double i ;
	double n ;
	double x[2][1] ;
	double y[2][1] ;
	double A[2][2] ;
	double B[2][2] ;
	n =10;
	*(*x+0)=1; 
	*(*x+1)=1; 
	*(*A+0)=1; 
	*(*A+1)=1; 
	*(*A+2)=1; 
	*(*A+3)=0; 
	*(*B+0)=1; 
	*(*B+1)=0; 
	*(*B+2)=0; 
	*(*B+3)=1; 
	printScalar(x);
	int i;
	for (i=1;i<n;i+=1){
		B =(A*B);
		y =(B*x);
		printScalar(y[1]);
	}
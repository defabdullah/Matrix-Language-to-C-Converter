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

	double A[3][3] ;
	double x[3][1] ;
	double y[3][1] ;
	double r ;
	double i ;
	*(*A+0)=0.5; 
	*(*A+1)=0; 
	*(*A+2)=0.5; 
	*(*A+3)=0; 
	*(*A+4)=0; 
	*(*A+5)=0.5; 
	*(*A+6)=0.5; 
	*(*A+7)=1; 
	*(*A+8)=0; 
	*(*x+0)=1; 
	*(*x+1)=1; 
	*(*x+2)=1; 
	int i;
	for (i=1;i<10;i+=1){
		y =(A*x);
		printScalar(r);
		x =y;
	}
	printsep();
	printScalar(x);
}
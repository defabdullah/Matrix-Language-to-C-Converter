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

	int i;
	for (i=1;i<42;i+=3){
	int j,i;
	for (j=2;j<58;j+=8){
		for(i=1;i<42;i+=3){
	double A[4][4] ;
	double count ;
	double incr ;
	double B[4][1] ;
	double i ;
	double j ;
	*(*A+0)=0; 
	*(*A+1)=1; 
	*(*A+2)=2; 
	*(*A+3)=3; 
	*(*A+4)=4; 
	*(*A+5)=5; 
	*(*A+6)=6; 
	*(*A+7)=7; 
	*(*A+8)=8; 
	*(*A+9)=9; 
	*(*A+10)=1; 
	*(*A+11)=1; 
	*(*A+12)=1; 
	*(*A+13)=2; 
	*(*A+14)=3; 
	*(*A+15)=4; 
	count =0;
	int i,j;
	for (i=1;i<45;i+=1){
		for(j=1;j<4;j+=1){
	printScalar(count);
}
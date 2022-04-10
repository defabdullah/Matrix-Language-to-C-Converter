#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


void printsep(){ 
	printf("------------\n"); 
}
double scalarSubstraction(double num1,double num2){
	return num1-num2;
}
double scalarSummation(double num1,double num2){
	return num1+num2;
}
double **matrixSubstraction( int row, int column, double *matrix1, double *matrix2 ){
	double * newMatrix=(double*)calloc(row*column,sizeof(double*));
	for(int i=0;i<row * column;i++){
		*(newMatrix + i) = *(matrix1 + i)-*(matrix2 + i);
	}double** resMatrix=&newMatrix;
	return resMatrix;
}
double **matrixSummation( int row, int column, double *matrix1, double *matrix2){
	double * newMatrix=(double*)calloc(row*column,sizeof(double*));
	for(int i=0;i<row * column;i++){
		*(newMatrix + i) = *(matrix1 + i)+*(matrix2 + i);
	}
	double** resMatrix=&newMatrix;
	return resMatrix;
}
double scalarMultiplication(double num1,double num2){
	return num1*num2;
}
double **scalarMatrixMultiplication(int row, int column,double scalar, double *matrix){
	double *newMatrix=(double*)calloc(column*row,sizeof(double*));
	for(int i=0;i<column;i++){
		for(int j=0;j<row;j++){
			*(newMatrix+(i*column+j))= scalar * (*(matrix + (i*row+j)));
		}
	}
	 double ** resMatrix=&newMatrix;
	return resMatrix;
}

void printScalar(double value){
	if( (int) value ==value){
		printf("%d\n",(int) value);
	}else{
		printf("%0.6f\n", value);
	} 
}
double **matrixTranspose(int column,int row,double *matrix){
	double *newMatrix=(double*)calloc(row*column,sizeof(double*));
	for(int i=0;i<column;i++){
		for(int j=0;j<row;j++){
			*(newMatrix+(i*column+j))= *(matrix + (j*column + i));
		}
	}
	double ** resMatrix=&newMatrix;
	return resMatrix;
}
double scalarTranspose(double num1){
	return num1;
}
double **matrixMultiplication( int a , int b,double *matrix1, int row1, int column1, double *matrix2, int row2, int column2){
	double *newMatrix=(double*)calloc(row1*column2,sizeof(double*));
	for(int i=0;i<row1;i++){
		for(int j=0;j<column2;j++){
			*(newMatrix+ (i*column2+j))=0;
			for(int k=0;k<row2;k++){
				*(newMatrix+ (i*column2+j)) += *(matrix1 + (i*column1+k) ) *  *(matrix2+ (k*column2+j));
			}
		}
	}
	double ** resMatrix= &newMatrix;
	return resMatrix;
}

void printMatrix(int row,int column,double *matrix){ 
	for(int i=0;i<row * column;i++){
		if(i%column==0 && i!=0){
			printf("\n");
		}
		if( (int) *(matrix + i) ==*(matrix + i)){
			printf("%d ",(int) *(matrix + i));
		}else{
			printf("%0.6f ", *(matrix + i));
		}
	}
	printf("\n");
}
double choose(double exp1, double exp2, double exp3, double exp4){
	if(exp1==0){
		return exp2;
	}
	else if (exp1>0){
		return exp3;
	}
	return exp4;
}
void matAssign(int row, int column, double* matrix,double* matrix2 ){
	for(int i=0;i<row * column;i++){
		*(matrix + i) = *(matrix2 + i);
	}
}
double getValue(int row, int column, double *A, int i, int j){
	return *(A + (i*row+j));
}


int main(){

	double A[3][3] ;
	double T[1][1] ;
	double x[3][1] ;
	double y[3][1] ;
	double i ;
	double r ;
	*(*A)=0.5; 
	*(*A+1)=0; 
	*(*A+2)=0.5; 
	*(*A+3)=0; 
	*(*A+4)=0; 
	*(*A+5)=0.5; 
	*(*A+6)=0.5; 
	*(*A+7)=1; 
	*(*A+8)=0; 
	*(*x)=1; 
	*(*x+1)=1; 
	*(*x+2)=1; 
	for (int i=1;i<=10;i+=1){
		matAssign(3,1,*y,*matrixMultiplication(3,1,*A,3,3,*x,3,1));
		matAssign(1,1,*T,*matrixMultiplication(1,1,*matrixTranspose(1,3,*matrixSubstraction(3,1,*y,*x)),1,3,*matrixSubstraction(3,1,*y,*x),3,1));
		r = sqrt(getValue(1,1,*T,1-1,1-1));
		printScalar(r);
		matAssign(3,1,*x,* y);
	}

	printsep();
	printMatrix(3,1,*x);
}
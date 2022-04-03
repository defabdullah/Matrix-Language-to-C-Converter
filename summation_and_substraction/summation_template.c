#include <stdio.h>
#include <stdlib.h>

double scalarSummation(double num1,double num2){
    return num1+num2;
}

/*double **matrixSummation( double **matrix1, double **matrix2, int row, int column){
    double **newMatrix;
    newMatrix=(double**)calloc(row,sizeof(double*));
    for(int i=0;i<row;i++){
        newMatrix[i]=(double*)calloc(column,sizeof(double));
    }
    
    //matrix multiplication
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            newMatrix[i][j]=(matrix1[i][j]+matrix2[i][j]);
        }
    }

    return newMatrix;
}*/

double **matrixSummation( double *matrix1, double *matrix2, int row, int column){
	double **newMatrix;
	newMatrix=(double**)calloc(row,sizeof(double*));
	for(int i=0;i<row;i++){
		newMatrix[i]=(double*)calloc(column,sizeof(double));
	}
	for(int i=0;i<row * column;i++){
			*(*newMatrix + i) = *(matrix1 + i)+*(matrix2 + i);		
	}
	return newMatrix;
}

void printMatrix(int row,int column,double **matrix){
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            printf("%f\n",matrix[i][j]);
        }
    }
}

int main() {

    int row=2;
    int column=2;

    //2 matrix declaration and assignment
    double **firstMatrix;
    firstMatrix=(double**) calloc(row,sizeof(double*));
    for(int i=0;i<row;i++){
        firstMatrix[i]=(double*)calloc(column,sizeof(double*));
    }

    double **secondMatrix;
    secondMatrix=(double**) calloc(column,sizeof(double*));
    for(int i=0;i<row;i++){
        secondMatrix[i]=(double*)calloc(row,sizeof(double*));
    }

    double array1[2][2]={{1.0,2.0},{3.0,4.0}};
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            firstMatrix[i][j]=array1[i][j];
        }
    }

    double array2[2][2]={{4.0,1.0},{7.0,3.0}};
    for(int i=0;i<column;i++){
        for(int j=0;j<row;j++){
            secondMatrix[i][j]=array2[i][j];
        }
    }
    
    printMatrix(row,column,firstMatrix);
    printf("----------------\n");
    printMatrix(row,column,secondMatrix);
    printf("----------------\n");

    //call matrix multiplication function
    double **resultMatrix=matrixSummation(firstMatrix,secondMatrix,2,2);

    printMatrix(row,column,resultMatrix);
    printf("\n%f",scalarSummation(3,7));

   return 0;
}
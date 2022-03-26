#include <stdio.h>
#include <stdlib.h>

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
    int scalar=3;

    //matrix definition with pointer
    double **firstMatrix;
    firstMatrix=(double**) calloc(row,sizeof(double*));
    for(int i=0;i<row;i++){
        firstMatrix[i]=(double*)calloc(column,sizeof(double*));
    }

    double array[2][2]={{1.0,2.0},{3.0,4.0}};
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            firstMatrix[i][j]=array[i][j];
        }
    }

    printMatrix(row,column,firstMatrix);
    printf("----------------\n");

    double **secondMatrix=scalarMatrixMultiplication(scalar,firstMatrix,row,column);

    printMatrix(row,column,secondMatrix);

   return 0;
}
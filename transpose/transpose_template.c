#include <stdio.h>
#include <stdlib.h>
double scalarTranspose(double num1){
        return num1;
    }

double **matrixTranspose(int row,int column,double **matrix){
    double **newMatrix;
    newMatrix=(double**)calloc(column,sizeof(double*));
    for(int i=0;i<column;i++){
        newMatrix[i]=(double*)calloc(row,sizeof(double));
    }

    for(int i=0;i<column;i++){
        for(int j=0;j<row;j++){
            newMatrix[i][j]=matrix[j][i];
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
    
    int row=3;
    int column=4;

    //matrix definition with pointer
    double **firstMatrix;
    firstMatrix=(double**) calloc(row,sizeof(double*));
    for(int i=0;i<row;i++){
        firstMatrix[i]=(double*)calloc(column,sizeof(double*));
    }

    double array[3][4]={{1.0,2.0,3.0,4.0},{5.0,6.0,7.0,8.0},{9.0,10.0,11.0,12.0}};
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            firstMatrix[i][j]=array[i][j];
        }
    }

    printMatrix(row,column,firstMatrix);
    printf("----------------\n");

    //call matrix transpose func
    double **secondMatrix=matrixTranspose(row,column,firstMatrix);
    // print matrix function (reverse row-column)
    printMatrix(column,row,secondMatrix);
    
   return 0;
}
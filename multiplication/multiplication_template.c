#include <stdio.h>
#include <stdlib.h>
int main() {
    double scalarMultiplication(double num1,double num2){
        return num1*num2;
    }

    double *scalarMatrixMultiplication(double scalar, double *matrix, int row, int column){
        double* newMatrix;
        newMatrix=malloc(sizeof(double*)*row*column);
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                *((newMatrix+i*column) + j) = *((matrix+i*column) + j)*scalar;
            }
        }
        return newMatrix;
    }
    void printMatrix(double *matrix,int row,int column){
        for(int i=0;i<row*column;i++){
            printf("%f\n",*(matrix+i));
        }
    }
    int row=2;
    int column=2;

    double array[2][2]={2,1,3,5};

    double *newmatrix=malloc(sizeof(double*)*row*column);
    newmatrix=scalarMatrixMultiplication(3,(&array)[0][0],row,column);

    printMatrix(newmatrix,row,column);

   return 0;
}
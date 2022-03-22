#include <stdio.h>
#include <stdlib.h>
int main() {
    int scalarMultiplication(int num1,int num2){
        return num1*num2;
    }

    int *scalarMatrixMultiplication(int scalar, int *matrix, int row, int column){
        int* newMatrix;
        newMatrix=malloc(sizeof(int*)*row*column);
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                *((newMatrix+i*column) + j) = *((matrix+i*column) + j)*scalar;
            }
        }
        return newMatrix;
    }
    void printMatrix(int *matrix,int row,int column){
        for(int i=0;i<row*column;i++){
            printf("%d\n",*(matrix+i));
        }
    }
    int row=2;
    int column=2;

    int array[2][2]={2,1,3,5};

    int *newmatrix=malloc(sizeof(int*)*row*column);
    newmatrix=scalarMatrixMultiplication(3,(&array)[0][0],row,column);

    printMatrix(newmatrix,row,column);
    
   return 0;
}
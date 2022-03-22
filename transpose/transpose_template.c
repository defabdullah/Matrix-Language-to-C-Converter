#include <stdio.h>
#include <stdlib.h>
int main() {
    double scalarTranspose(double num1){
        return num1;
    }

    double *matrixTranspose(double *matrix, int row, int column){
        double* newMatrix;
        newMatrix=malloc(sizeof(double*)*row*column);
        for(int i=0;i<column;i++){
            for(int j=0;j<row;j++){
                *(newMatrix+i*row+j) = *(matrix+(j*column+i));
            }
        }
        return newMatrix;
    }
    
    void printMatrix(double *matrix,int row,int column){
        for(int i=0;i<row*column;i++){
            printf("%f\n",*(matrix+i));
        }
    }

    int row=4;
    int column=3;

    double array[4][3]={{2.4,1.42,3.214},{5.325,34.153,158.12},{26.214,125.12,23.32},{632214.32,94.14,2.1}};
    
    double *newmatrix=malloc(sizeof(double*)*row*column);
    newmatrix=matrixTranspose((&array)[0][0],row,column);
    printMatrix(newmatrix,row,column);
    
   return 0;
}
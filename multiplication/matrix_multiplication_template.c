#include <stdio.h>
#include <stdlib.h>



/*double **matrixMultiplication( double **matrix1, int row1, int column1, double **matrix2, int row2, int column2){
    double **newMatrix;
    newMatrix=(double**)calloc(row1,sizeof(double*));
    for(int i=0;i<row1;i++){
       newMatrix[i]=(double*)calloc(column2,sizeof(double));
    }
    
    //matrix multiplication
    for(int i=0;i<row1;i++){
        for(int j=0;j<column2;j++){
            newMatrix[i][j]=0;
            for(int k=0;k<row2;k++){
                newMatrix[i][j]+=(matrix1[i][k]*matrix2[k][j]);
            }
        }
    }

    return newMatrix;
}*/
/*double **matrixMultiplication( int a , int b,double *matrix1, int row1, int column1, double *matrix2, int row2, int column2){
	double **newMatrix=(double**)calloc(row1,sizeof(double*));
	for(int i=0;i<row1;i++){
		newMatrix[i]=(double*)calloc(column2,sizeof(double));
	}
	for(int i=0;i<row1;i++){
		for(int j=0;j<column2;j++){
			newMatrix[i][j]=0;
			for(int k=0;k<row2;k++){
				newMatrix[i][j]+= *(matrix1 + (i*row1+k) ) *  *(matrix2+ (k*row2+j));
			}
		}
	}
	return newMatrix;
}*/
double **matrixMultiplication( int a , int b,double *matrix1, int row1, int column1, double *matrix2, int row2, int column2){
	double *newMatrix=(double*)calloc(row1*column2,sizeof(double*));
	for(int i=0;i<row1;i++){
		for(int j=0;j<column2;j++){
			*(newMatrix+ (i*row1+j))=0;
			for(int k=0;k<row2;k++){
				*(newMatrix+ (i*row1+j)) += *(matrix1 + (i*row1+k) ) *  *(matrix2+ (k*row2+j));
			}
		}
	}
	double ** resMatrix= &newMatrix;
	return resMatrix;
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
    printMatrix(column,row,secondMatrix);
    printf("----------------\n");

    //call matrix multiplication function
    double **resultMatrix=matrixMultiplication(firstMatrix,2,2,secondMatrix,2,2);

    printMatrix(row,column,resultMatrix);

   return 0;
}
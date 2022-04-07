#include <stdio.h>

double getValue(int row, int column, double *A, int i, int j){
    return *(A + (i*row+j));
}

int main(){
    double A[4][2];
    *(*A+0)=0; 
	*(*A+1)=1; 
	*(*A+2)=2; 
	*(*A+3)=3;
    *(*A+4)=4; 
	*(*A+5)=5; 
	*(*A+6)=6; 
	*(*A+7)=7; 
    for (int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            printf("%f\n",getValue(4,2,*A,i,j));

        }
    }
    return 0;
}
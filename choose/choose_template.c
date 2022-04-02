#include <stdio.h>
double choose(double exp1, double exp2, double exp3, double exp4){
    if(exp1==0){
        return exp2;
    }
    else if (exp1>0){
        return exp3;
    }
    return exp4;
}



int main(){
    printf("%f",choose(20,32,31,54));
}
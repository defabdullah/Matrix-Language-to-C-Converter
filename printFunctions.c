#include "main.h"


void printSingleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition){
    fprintf(pOutputFile,"\tfor (int %s=%s;%s<=%s;%s+=%s){\n",firstInitVariable,firstInitAssignment,firstInitVariable,firstCondition,firstInitVariable,firstAddition);
}

void printDoubleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition, char* secondInitVariable, char* secondInitAssignment, char* secondCondition, char* secondAddition){
    fprintf(pOutputFile,"\tfor (int %s=%s;%s<=%s;%s+=%s){\n\t\tfor( int %s=%s;%s<=%s;%s+=%s){\n",firstInitVariable,firstInitAssignment,firstInitVariable,firstCondition,firstInitVariable,firstAddition,secondInitVariable,secondInitAssignment,secondInitVariable,secondCondition,secondInitVariable,secondAddition);
}

void printScalarSubstraction(){
    fprintf(pOutputFile,"%s","double scalarSubstraction(double num1,double num2){\n\treturn num1-num2;\n}\n");
}

void printScalarSummation(){
    fprintf(pOutputFile,"%s","double scalarSummation(double num1,double num2){\n\treturn num1+num2;\n}\n");
}

void printMatrixSubstraction(){
    fprintf(pOutputFile,"%s","double **matrixSubstraction( int row, int column, double *matrix1, double *matrix2 ){\n\tdouble * newMatrix=(double*)calloc(row*column,sizeof(double*));\n\tfor(int i=0;i<row * column;i++){\n\t\t*(newMatrix + i) = *(matrix1 + i)-*(matrix2 + i);\n\t}double** resMatrix=&newMatrix;\n\treturn resMatrix;\n}\n");
}

void printMatrixSummation(){
    fprintf(pOutputFile,"%s","double **matrixSummation( int row, int column, double *matrix1, double *matrix2){\n\tdouble * newMatrix=(double*)calloc(row*column,sizeof(double*));\n\tfor(int i=0;i<row * column;i++){\n\t\t*(newMatrix + i) = *(matrix1 + i)+*(matrix2 + i);\n\t}\n\tdouble** resMatrix=&newMatrix;\n\treturn resMatrix;\n}\n");
}
void printScalarMultiplication(){
    fprintf(pOutputFile,"%s","double scalarMultiplication(double num1,double num2){\n\treturn num1*num2;\n}\n");
}

void printScalarMatrixMultiplication(){
    fprintf(pOutputFile,"%s","double **scalarMatrixMultiplication(int row, int column,double scalar, double *matrix){\n\tdouble *newMatrix=(double*)calloc(column*row,sizeof(double*));\n\tfor(int i=0;i<column;i++){\n\t\tfor(int j=0;j<row;j++){\n\t\t\t*(newMatrix+(i*column+j))= scalar * (*(matrix + (i*row+j)));\n\t\t}\n\t}\n\t double ** resMatrix=&newMatrix;\n\treturn resMatrix;\n}\n");
}

void printPrintScalar(){
    fprintf(pOutputFile,"%s","\nvoid printScalar(double value){\n\tif( (int) value ==value){\n\t\tprintf(\"%d\\n\",(int) value);\n\t}else{\n\t\tprintf(\"%0.6f\\n\", value);\n\t} \n}");
}

void printMatrixTranspose(){
    fprintf(pOutputFile,"%s","\ndouble **matrixTranspose(int column,int row,double *matrix){\n\tdouble *newMatrix=(double*)calloc(row*column,sizeof(double*));\n\tfor(int i=0;i<column;i++){\n\t\tfor(int j=0;j<row;j++){\n\t\t\t*(newMatrix+(i*column+j))= *(matrix + (j*column + i));\n\t\t}\n\t}\n\tdouble ** resMatrix=&newMatrix;\n\treturn resMatrix;\n}\n");
}

void printScalarTranspose(){
    fprintf(pOutputFile,"%s","double scalarTranspose(double num1){\n\treturn num1;\n}\n");
}

void printChoose(){
    fprintf(pOutputFile,"%s","double choose(double exp1, double exp2, double exp3, double exp4){\n\tif(exp1==0){\n\t\treturn exp2;\n\t}\n\telse if (exp1>0){\n\t\treturn exp3;\n\t}\n\treturn exp4;\n}\n");
}

void printCloseBracket(){
    fprintf(pOutputFile,"%s","}");
}

void printsep(){
    fprintf(pOutputFile,"%s","\n\tprintsep();\n");
}

void printPrintMatrix(){
    fprintf(pOutputFile,"%s","\nvoid printMatrix(int row,int column,double *matrix){ \n\tfor(int i=0;i<row * column;i++){\n\t\tprintScalar(*(matrix + i));\n\t}\n}\n");
}

void printAssignMat(){
    fprintf(pOutputFile,"%s","void matAssign(int row, int column, double* matrix,double* matrix2 ){\n\tfor(int i=0;i<row * column;i++){\n\t\t*(matrix + i) = *(matrix2 + i);\n\t}\n}\n");
}

void printMatrixMultiplication(){
    fprintf(pOutputFile,"%s","double **matrixMultiplication( int a , int b,double *matrix1, int row1, int column1, double *matrix2, int row2, int column2){\n\tdouble *newMatrix=(double*)calloc(row1*column2,sizeof(double*));\n\tfor(int i=0;i<row1;i++){\n\t\tfor(int j=0;j<column2;j++){\n\t\t\t*(newMatrix+ (i*column2+j))=0;\n\t\t\tfor(int k=0;k<row2;k++){\n\t\t\t\t*(newMatrix+ (i*column2+j)) += *(matrix1 + (i*column1+k) ) *  *(matrix2+ (k*column2+j));\n\t\t\t}\n\t\t}\n\t}\n\tdouble ** resMatrix= &newMatrix;\n\treturn resMatrix;\n}\n");
}

void printGetValue(){
    fprintf(pOutputFile,"%s","double getValue(int row, int column, double *A, int i, int j){\n\treturn *(A + (i*row+j));\n}\n");
}

void print_usual(){
    fprintf(pOutputFile, "%s","#include <stdio.h>\n#include <string.h>\n#include <ctype.h>\n#include <stdlib.h>\n#include <math.h>\n\n");
    fprintf(pOutputFile,"%s","\nvoid printsep(){ \n\tprintf(\"------------\\n\"); \n}\n");
    printScalarSubstraction();
    printScalarSummation();
    printMatrixSubstraction();
    printMatrixSummation();
    printScalarMultiplication();
    printScalarMatrixMultiplication();
    printPrintScalar();
    printMatrixTranspose();
    printScalarTranspose();
    printMatrixMultiplication();
    printPrintMatrix();
    printChoose();
    printAssignMat();
    printGetValue();
    fprintf(pOutputFile,"%s","\n\nint main(){\n\n");
}
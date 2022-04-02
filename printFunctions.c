#include "main.h"


void printSingleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition){
    fprintf(pOutputFile,"\tint %s;\n\tfor (%s=%s;%s<%s;%s+=%s){\n",firstInitVariable,firstInitVariable,firstInitAssignment,firstInitVariable,firstCondition,firstInitVariable,firstAddition);
}

void printDoubleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition, char* secondInitVariable, char* secondInitAssignment, char* secondCondition, char* secondAddition){
    fprintf(pOutputFile,"\tint %s,%s;\n\tfor (%s=%s;%s<%s;%s+=%s){\n\t\tfor(%s=%s;%s<%s;%s+=%s){\n",firstInitVariable,secondInitVariable,firstInitVariable,firstInitAssignment,firstInitVariable,firstCondition,firstInitVariable,firstAddition,secondInitVariable,secondInitAssignment,secondInitVariable,secondCondition,secondInitVariable,secondAddition);
}

void printScalarMultiplication(){
    fprintf(pOutputFile,"%s","double scalarMultiplication(double num1,double num2){\n\treturn num1*num2;\n}\n");
}

void printScalarMatrixMultiplication(){
    fprintf(pOutputFile,"%s","double **scalarMatrixMultiplication(double scalar, double **matrix, int row, int column){\n\tdouble **newMatrix;\n\tnewMatrix=(double**)calloc(column,sizeof(double*));\n\tfor(int i=0;i<column;i++){\n\t\tnewMatrix[i]=(double*)calloc(row,sizeof(double));\n\t}\n\n\tfor(int i=0;i<column;i++){\n\t\tfor(int j=0;j<row;j++){\n\t\t\tnewMatrix[i][j]=(scalar*matrix[i][j]);\n\t\t}\n\t}\n\n\treturn newMatrix;\n}\n");
}

void printPrintScalar(){
    fprintf(pOutputFile,"%s","\nvoid printScalar(double value){\n\tif( (int) value ==value){\n\t\tprintf(\"%d\",(int) value);\n\t}else{\n\t\tprintf(\"%0.7f\", value);\n\t} \n}");
}

void printMatrixTranspose(){
    fprintf(pOutputFile,"%s","\ndouble **matrixTranspose(int row,int column,double **matrix){\n\tdouble **newMatrix;\n\tnewMatrix=(double**)calloc(column,sizeof(double*));\n\tfor(int i=0;i<column;i++){\n\t\tnewMatrix[i]=(double*)calloc(row,sizeof(double));\n\t}\n\tfor(int i=0;i<column;i++){\n\t\tfor(int j=0;j<row;j++){\n\t\t\tnewMatrix[i][j]=matrix[j][i];\n\t\t}\n\t}\n\treturn newMatrix;\n}\n");
}

void printChoose(){
    fprintf(pOutputFile,"%s","double choose(double exp1, double exp2, double exp3, double exp4){\n\tif(exp1==0){\n\t\treturn exp2;\n\t}\n\telse if (exp1>0){\n\t\treturn exp3;\n\t}\n\treturn exp4;\n}");
}

void printCloseBracket(){
    fprintf(pOutputFile,"%s","}");
}

void printsep(){
    fprintf(pOutputFile,"%s","\n\tprintsep();\n");
}

void print_usual(){
    fprintf(pOutputFile, "%s","#include <stdio.h>\n#include <string.h>\n#include <ctype.h>\n\n");
    fprintf(pOutputFile,"%s","\nvoid printsep(){ \n\tprintf(\"----------\\n\"); \n}\n");
    printScalarMultiplication();
    printScalarMatrixMultiplication();
    printPrintScalar();
    printMatrixTranspose();
    printChoose();
    fprintf(pOutputFile,"%s","\n\nint main(){\n\n");
}
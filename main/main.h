#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

enum types{scalar,vector,matrix};

FILE *pInputFile;
FILE *pOutputFile;

int lineNumber;

char * special_functions;

/*extern void printSingleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition);
extern void printDoubleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition, char* secondInitVariable, char* secondInitAssignment, char* secondCondition, char* secondAddition);
extern void printScalarMultiplication();
extern void printScalarMatrixMultiplication();
extern void printPrintScalar();*/
extern void printCloseBracket();
extern void print_usual();
extern void printsep();

extern char* strrev ( char* str);
extern char *trim(char *s);

extern int is_alphanumeric(char* s);
extern int is_alphanumeric_string(char* s);
extern int is_numeric_string(char *s);
extern int expression_divider(char* line,char *first,char *second);


extern void scalar_line(char* line);
extern void vector_line(char* line);
extern void matrix_line(char* line);

extern char* summation(char *first,char* second);
extern char* substraction(char *first,char* second);
extern char* multiplication(char *first,char* second);
extern char* expression_parser(char *line);

extern void exit_program(int lineNumber);

extern void matrix_initializer(char * statement,char* variable_name);
extern void assignment_statement(char * statement,char* variable_name);
extern void print_line(char * line);

#endif
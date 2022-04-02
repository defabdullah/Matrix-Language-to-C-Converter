#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


//main

enum types {scalar,vector,matrix,empty};
enum special_functions {tr,choose,sqrt,none};
enum types isDeclared(char *str);

FILE *pInputFile;
FILE *pOutputFile;

int lineNumber;
int scalarNumber;
int vectorNumber;
int matrixNumber;
char *scalarArray[256];
char *vectorArray[256];
char *matrixArray[256];

//statement functions

extern void matrix_initializer(char * statement,char* variable_name);
extern void assignment_statement(char * statement,char* variable_name);
extern void print_line(char * line);


extern char* summation(char *first,char* second);
extern char* substraction(char *first,char* second);
extern char* multiplication(char *first,char* second);
extern char* expression_parser(char *line);
extern char* strrev (char* str);

extern void scalar_line(char* line);
extern void vector_line(char* line);
extern void matrix_line(char* line);


//parsing functions
extern char *trim(char *s);

extern int is_alphanumeric(char* s);
extern int is_alphanumeric_string(char* s);
extern int is_numeric_string(char *s);
extern int expression_divider(char* line,char *first,char *second);
extern void exit_program();



//print functions
extern void printCloseBracket();
extern void print_usual();
extern void printsep();
extern void printSingleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition);
extern void printDoubleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition, char* secondInitVariable, char* secondInitAssignment, char* secondCondition, char* secondAddition);


//paranthesis parser
extern char *parseParanthesis(char *str);
extern char *deleteParanthesis(char *str);

char *reverse;
char *reverseStr;
char *reverseCopy;
char *reverseFull;
char *withoutLastParanthesis;

char *afterParantReverse;
char *afterParant;
char *beforeParantReverse;
char *beforeParant;

char *afterParantModified;
char *innerExpression;
char *result;

//for parser
char *temp;

char *initVariables;
 
char *firstInitVariable;
char *firstParameters;
char *firstInitAssignment;
char *firstCondition;
char *firstAddition;

char *secondInitVariable;
char *secondParameters;
char *secondInitAssignment;
char *secondCondition;
char *secondAddition;
 
extern void parseSingleFor(char *str);
extern void parseDoubleFor(char *str);

void tokenControl(char *str,char *correctToken);

#endif
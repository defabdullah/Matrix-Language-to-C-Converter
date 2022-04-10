#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


//funciton and type enums

enum types {scalar,vector,matrix,empty};
enum special_functions {tr,choose,sqrt,none};

//functions which return type of expressionor special function
enum types isDeclared(char *str);
enum special_functions is_special_funciton(char * token);

//input and output files
FILE *pInputFile;
FILE *pOutputFile;

//current line number
int lineNumber;

//index for storing variables
int scalarNumber;
int vectorNumber;
int matrixNumber;

//arrays which stores variables according to their types
char *scalarArray[256];
char *vectorArray[256];
char *matrixArray[256];

//arrays which stores size of 2 size of matrixes and size of vectors
char *matrix_row_sizes[256];
char *matrix_column_sizes[256];
char *vector_sizes[256];


//declaration functions
//parse declarations and control their form and if it is suitable for decleration it prints them 

extern void scalar_line(char *line);
extern void vector_line(char *line);
extern void matrix_line(char *line);

//assignment functions

//controls and send to parser funciton then prints the result in correct form
extern void assignment_statement(char * statement,char* variable_name);
//controls and send to parser funciton then prints the print functions in correct form
extern void print_line(char * line);

//functions which return sizes using size arrays
extern char *matrixFirstSize(char *mat);
extern char *matrixSecondSize(char *mat);
extern char *vectorSize(char *mat);
extern char *first_size(char *mat);
extern char *second_size(char *mat);

//function which takes expression withouth paranthesis and split them according to bnf and right recursive rule
//it uses recursion until it takes single token
extern char *expression_parser(char *str);

//parsing functions which help to parse expressions
extern char *trim(char *s);
//global variable which uses in strrev function
char *reverse;
//reverse function
extern char* strrev (char* str);
//helper functions
extern int is_valid_variable_name(char *str);
extern int is_alphanumeric(char* s);
extern int is_alphanumeric_or_comma(char* s);
extern int is_alphanumeric_string(char* s);
extern int is_numeric_string(char *s);
extern int return_type_of_function(char *token);

//print functions
extern void printCloseBracket();
extern void print_usual();
extern void printsep();
extern void printSingleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition);
extern void printDoubleForOpening(char* firstInitVariable, char* firstInitAssignment, char* firstCondition, char* firstAddition, char* secondInitVariable, char* secondInitAssignment, char* secondCondition, char* secondAddition);

//function which take expressions full form and send them to correct functions to return correct form
extern char *parseParanthesis(char *str);

// clear all outer paranthesis
extern char *deleteParanthesis(char *str);

//choose parser funciton and global return variable
char *chooseParser(char *str);
char chooseResult[5000];

//for parser functions
extern void parseSingleFor(char *str);
extern void parseDoubleFor(char *str);

//exits program and gives error function
extern void exit_program();

#endif
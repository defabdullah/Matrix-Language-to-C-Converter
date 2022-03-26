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

void printScalarMultiplication();
void printScalarMatrixMultiplication();
void print_usual();

#endif
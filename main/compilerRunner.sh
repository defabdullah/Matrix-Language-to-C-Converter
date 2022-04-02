#!/bin/bash
gcc -Wall -c printFunctions.c
gcc -Wall -c parsingFunctions.c
gcc -Wall -c declarationFunctions.c
gcc -Wall -c expressionParser.c
gcc -Wall -c statementFunctions.c
gcc -Wall -c main.c
gcc -o main.out printFunctions.o parsingFunctions.o main.o declarationFunctions.o expressionParser.o statementFunctions.o
./main.out trial.txt
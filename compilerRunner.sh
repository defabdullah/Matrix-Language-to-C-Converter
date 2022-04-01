#!/bin/bash
gcc -Wall -c printFunctions.c parsingFunctions.c declarationFunctions.c expressionParser.c
gcc  main.c printFunctions.o parsingFunctions.o declarationFunctions.o expressionParser.o -o main.out -Wall
./main.out
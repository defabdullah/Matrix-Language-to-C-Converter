#!/bin/bash
gcc -Wall -c printFunctions.c
gcc -Wall -c parsingFunctions.c
gcc -Wall -c declarationFunctions.c
gcc -Wall -c main.c
gcc -o testprogram printFunctions.o parsingFunctions.o main.o declarationFunctions.o
./testprogram trial.txt
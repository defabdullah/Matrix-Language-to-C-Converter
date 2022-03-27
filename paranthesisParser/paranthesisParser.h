#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* strrev ( char* str);
char *parseParanthesis(char *str);

char *reverseStr;
char *reverseCopy;

char *afterParantReverse;
char *afterParant;

char *beforeParantReverse;
char *beforeParant;

char *afterParantModified;
char *temp;
char *result;

#endif

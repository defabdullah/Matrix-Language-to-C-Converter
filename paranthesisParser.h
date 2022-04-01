#ifndef PARANTHESIS_PARSER_H
#define PARANTHESIS_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../main/main.h"


char *parseParanthesis(char *str);

char *reverseStr;
char *reverseCopy;

char *afterParantReverse;
char *afterParant;

char *beforeParantReverse;
char *beforeParant;

char *afterParantModified;
char *innerExpression;
char *result;

#endif

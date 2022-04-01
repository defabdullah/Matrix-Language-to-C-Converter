#ifndef FOR_PARSER_H
#define FOR_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

char *parseSingleFor(char *str);
char *parseDoubleFor(char *str);

#endif

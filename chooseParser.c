#include "main.h"

char *chooseParser(char *str){
    char *copy=strdup(str);
    char *token;
    char result[5000];

    int tokenNum=1;
    char *expressionOne;
    char *expressionTwo;
    char *expressionThree;
    char *expressionFour;

    while((token=strsep(&copy,","))!=NULL){
        if(tokenNum==1){
            expressionOne=strdup(parseParanthesis(token));
        }

        else if(tokenNum==2){
            expressionTwo=strdup(parseParanthesis(token));
        } 

        else if(tokenNum==3){
            expressionThree=strdup(parseParanthesis(token));
        }

        else if(tokenNum==4){
            expressionFour=strdup(parseParanthesis(token));
        }
        else{
            exit_program();
        }

    }

    strcat(result," ( ");
    strcat(result,expressionOne);
    strcat(result," , ");
    strcat(result,expressionTwo);
    strcat(result," , ");
    strcat(result,expressionThree);
    strcat(result," , ");
    strcat(result,expressionFour);
    strcat(result," ) ");

    return result;

}
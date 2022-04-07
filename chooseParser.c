#include "main.h"

char *chooseParser(char *str){
    char *copy=strdup(str);
    char *token;

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

        tokenNum++;

    }

    strcat(chooseResult," ( ");


    strcat(chooseResult,expressionOne);
    strcat(chooseResult," , ");
    strcat(chooseResult,expressionTwo);

    strcat(chooseResult," , ");

    strcat(chooseResult,expressionThree);

    strcat(chooseResult," , ");

    strcat(chooseResult,expressionFour);
    strcat(chooseResult," ) ");

    return chooseResult;

}
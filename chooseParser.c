#include "main.h"

char *chooseParser(char *str){

    char *copy=strdup(str);
    char *token;

    int tokenNum=1;
    char *expressionOne;
    char *expressionTwo;
    char *expressionThree;
    char *expressionFour;
    char exp[5000];
    int is_inbracket =0;
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        if(strcmp(token,"[")==0){
            is_inbracket=1;
        }else if(strcmp(token,"]")==0){
            is_inbracket=0;
        }
        if(strcmp(token,",")!=0 || is_inbracket==1){
            strcat(exp,token);
            strcat(exp," ");
            continue;
        }
        if(is_inbracket==1){
            continue;
        }


            if(tokenNum==1){
                expressionOne=strdup(parseParanthesis(exp));

            }
            else if(tokenNum==2){
                expressionTwo=strdup(parseParanthesis(exp));

            } 
            else if(tokenNum==3){
                expressionThree=strdup(parseParanthesis(exp));

            }
  
            else{
                exit_program();
            }
            tokenNum++;
            memset(exp,0,5000);
    }

    expressionFour=strdup(parseParanthesis(exp));
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
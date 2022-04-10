#include "main.h"

//takes 4 choose expressions and send all of them to paranthesis parser to return correct expressions and return all expressions
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

    //iterates over tokens and send expression until it sees comma
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        
        //control in brackets state for seperate matrix indexing situations and choose expressions
        if(strcmp(token,"[")==0){
            is_inbracket=1;
        }else if(strcmp(token,"]")==0){
            is_inbracket=0;
        }

        //until comma it merges token to form whole expression
        if(strcmp(token,",")!=0 || is_inbracket==1){
            strcat(exp,token);
            strcat(exp," ");
            continue;
        }

        //if it tokens are in brackets continue to merge tokens
        if(is_inbracket==1){
            continue;
        }

        //send expression to paranthesis parser to return expression with correct forms   
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

    //since last expression don't have comma in its end it sends all expression 
    expressionFour=strdup(parseParanthesis(exp));

    //merges and return choose function with correct expressions
    strcat(chooseResult," ( ");strcat(chooseResult,expressionOne);strcat(chooseResult," , ");strcat(chooseResult,expressionTwo);strcat(chooseResult," , ");strcat(chooseResult,expressionThree);strcat(chooseResult," , ");strcat(chooseResult,expressionFour);strcat(chooseResult," ) ");
    return chooseResult;

}
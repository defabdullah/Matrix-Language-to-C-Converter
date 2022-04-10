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
    memset(exp,0,5000);
    int chooseStack =0;
    int parantStack=0;
    //iterates over tokens and send expression until it sees comma

    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }

        //control in brackets state for seperate matrix indexing situations and choose expressions
        if(strcmp(token,"[")==0){
            chooseStack++;
        }else if(strcmp(token,"]")==0){
            chooseStack--;
        }
        else if(strcmp(token,"(")==0){
            parantStack++;
        }else if(strcmp(token,")")==0){
            parantStack--;
        }
        printf("tok: %s\n",token);
        //until comma it merges token to form whole expression
        if(strcmp(token,",")!=0 || chooseStack!=0 || parantStack!=0){
            strcat(exp,token);
            strcat(exp," ");
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
        chooseStack=0;

        tokenNum++;
        memset(exp,0,5000);
    }

    //since last expression don't have comma in its end it sends all expression 
    if(tokenNum==4){
        expressionFour=strdup(parseParanthesis(exp));
    }
    else{
        exit_program();
    }
    //printf("exp: %s\n",exp);

    memset(chooseResult,0,5000);
    //merges and return choose function with correct expressions
    strcat(chooseResult," ( ");strcat(chooseResult,expressionOne);strcat(chooseResult," , ");strcat(chooseResult,expressionTwo);strcat(chooseResult," , ");strcat(chooseResult,expressionThree);strcat(chooseResult," , ");strcat(chooseResult,expressionFour);strcat(chooseResult," ) ");
    return chooseResult;

}
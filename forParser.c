#include "main.h"

void parseSingleFor(char *str){
    
    char *temp=strtok(strrev(str)," ");
    tokenControl(strtok(temp," "),"{");

    str=deleteParanthesis(str);
    
    firstInitVariable=strtok(str," ");
    
    tokenControl(strtok(NULL," "),"in");

    //get all parameters && : control tokens
    firstInitAssignment=strtok(NULL," ");
    
    tokenControl(strtok(NULL," "),":");
    
    firstCondition=strtok(NULL," ");
    
    tokenControl(strtok(NULL," "),":");

    firstAddition=strtok(NULL," ");

    printSingleForOpening(firstInitVariable,firstInitAssignment,firstCondition,firstAddition);
    
}

void parseDoubleFor(char *str){

    char *temp=strtok(strrev(str)," ");
    
    tokenControl(temp,"{");

    str=deleteParanthesis(str);


    firstInitVariable=strtok(str," ");

    tokenControl(strtok(NULL," "),",");

    secondInitVariable=strtok(NULL," ");

    tokenControl(strtok(NULL," "),"in");

    //get first parameters && : control tokens
    firstInitAssignment=strtok(NULL," ");
    tokenControl(strtok(NULL," "),":");
    firstCondition=strtok(NULL," ");
    tokenControl(strtok(NULL," "),":");
    firstAddition=strtok(NULL," ");
        
    tokenControl(strtok(NULL," "),",");

    //get second parameters && : control tokens
    secondInitAssignment=strtok(NULL," ");
    tokenControl(strtok(NULL," "),":");
    secondCondition=strtok(NULL," ");
    tokenControl(strtok(NULL," "),":");
    secondAddition=strtok(NULL," ");

    printDoubleForOpening(firstInitVariable,firstInitAssignment,firstCondition,firstAddition,secondInitVariable,secondInitAssignment,secondCondition,secondAddition);
    
}

void tokenControl(char *str,char *correctToken){
    if(strcmp(str,correctToken)!=0){
        exit_program();
    }
}

/*
int main(){
    char doubleFor[]="i,j in 2:45:25,5:42:75";
    char singleFor[]="i in 2:5:9";
    //printf("%s\n",parseSingleFor(singleFor));
    printf("%s\n",parseDoubleFor(doubleFor));
    return 0;
}*/



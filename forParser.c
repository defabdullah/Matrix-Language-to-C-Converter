#include "main.h"

void tokenControl(char *str,char *correctToken){
    if(strcmp(str,correctToken)!=0){
        exit_program();
    }
}

void parseSingleFor(char *str){
    char *firstInitVariable;
    char *firstInitAssignment;
    char *firstCondition;
    char *firstAddition;
    char *temp=strtok(strrev(str)," ");

    tokenControl(strtok(temp," "),"{");

    str=deleteParanthesis(str);
    int iteration=1;
    char *token;
    while((token=strsep(&str," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        if(iteration==1){
            firstInitVariable=token;
        }
        else if(iteration==2){
            tokenControl(token,"in");
            
        }
        else if(iteration==3){
            firstInitAssignment=parseParanthesis(token);
            
        }
        else if(iteration==4){
            tokenControl(token,":");
        }
        else if(iteration==5){
            firstCondition=parseParanthesis(token);
            
        }
        else if(iteration==6){
            tokenControl(token,":");
        }
        else if(iteration==7){
            firstAddition=parseParanthesis(token);
        }
        else{
            exit_program();
        }
        iteration++;
    }
    printSingleForOpening(firstInitVariable,firstInitAssignment,firstCondition,firstAddition);
    
}

void parseDoubleFor(char *str){
    char *firstInitVariable;
    char *firstInitAssignment;
    char *firstCondition;
    char *firstAddition;
    char *secondInitVariable;
    char *secondInitAssignment;
    char *secondCondition;
    char *secondAddition;
    char *temp=strtok(strrev(str)," ");
    
    tokenControl(temp,"{");
    str=deleteParanthesis(str);

    int iteration=1;
    char *token;
    while((token=strsep(&str," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        if(iteration==1){
            firstInitVariable=token;
        }
        else if(iteration==2){
            tokenControl(token,",");
            
        }
        else if(iteration==3){
            secondInitVariable=token;
            
        }
        else if(iteration==4){
            tokenControl(token,"in");
        }
        else if(iteration==5){
            firstInitAssignment=parseParanthesis(token);
            
        }
        else if(iteration==6){
            tokenControl(token,":");
        }

        else if(iteration==7){
            firstCondition=parseParanthesis(token);
        }

        else if(iteration==8){
            tokenControl(token,":");
        }

        else if(iteration==9){
            firstAddition=parseParanthesis(token);
        }
        else if(iteration==10){
            tokenControl(token,",");
        }
        else if(iteration==11){
            secondInitAssignment=parseParanthesis(token);
        }
        else if(iteration==12){
            tokenControl(token,":");
        }
        else if(iteration==13){
            secondCondition=parseParanthesis(token);
        }
        else if(iteration==14){
            tokenControl(token,":");
        }
        else if(iteration==15){
            secondAddition=parseParanthesis(token);
        }
        else{
            exit_program();
        }
        iteration++;
    }
    printDoubleForOpening(firstInitVariable,firstInitAssignment,firstCondition,firstAddition,secondInitVariable,secondInitAssignment,secondCondition,secondAddition);
}

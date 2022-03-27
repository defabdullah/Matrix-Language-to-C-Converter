#include "forParser.h"

char *parseSingleFor(char *str){
    firstInitVariable=strtok(str," ");
    temp=strtok(NULL," ");
    
    if(strcmp(temp,"in")!=0){
        printf("sikinti\n");
    }

    //get all parameters
    firstInitAssignment=strtok(NULL,":");
    firstCondition=strtok(NULL,":");
    firstAddition=strtok(NULL,":");
    return firstAddition;
}

char *parseDoubleFor(char *str){
    initVariables=strtok(str," ");
    temp=strtok(NULL, " ");

    if(strcmp(temp,"in")!=0){
        printf("sikinti\n");
    }

    //take 3 exp parameters like 1:45:46
    firstParameters=strtok(NULL,",");
    secondParameters=strtok(NULL,"");

    //take init variables like i,j
    firstInitVariable=strtok(initVariables,",");
    secondInitVariable=strtok(NULL," ");
    
    //take first loop parameters
    firstInitAssignment=strtok(firstParameters,":");
    firstCondition=strtok(NULL,":");
    firstAddition=strtok(NULL,"");

    //take second loop parameters
    secondInitAssignment=strtok(secondParameters,":");
    secondCondition=strtok(NULL,":");
    secondAddition=strtok(NULL,"");

    return secondInitVariable;
}

int main(){
    char doubleFor[]="i,j in 2:45:25,5:42:75";
    char singleFor[]="i in 2:5:9";
    //printf("%s\n",parseSingleFor(singleFor));
    printf("%s\n",parseDoubleFor(doubleFor));
    return 0;
}



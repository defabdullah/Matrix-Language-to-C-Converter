#include "paranthesisParser.h"


//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){

    //if there is no paranthesis send expression to expression function
    if(strstr(str,"(")==NULL){

        //incomplete ex: op=expression(after)
        return expression_parser(innerExpression);
    }

    //take it's reverse
    reverseStr=strrev(str);

    //create reverse copy string
    reverseCopy = (char *)malloc(strlen(str) + 1);
    strcpy(reverseCopy,reverseStr);

    //string after paranthesis
    afterParantReverse=strtok(reverseCopy,"(");
    afterParant=strrev(afterParantReverse);


    //string before paranthesis
    beforeParantReverse=strtok(NULL,"");
    beforeParant=strrev(beforeParantReverse);

    //create string after paranthesis
    innerExpression=parseParanthesis(strtok(afterParant, ")"));
    return "beforeParant";
    afterParantModified=strtok(NULL,"");

    //concatenate string after changing expression with old value 
    
    result=strcat(beforeParant,innerExpression);
    if(afterParantModified!=NULL){
        return strcat(result,afterParantModified);
    }

    return result;
}

int main(){
    printf("asf");
    char str[]="tr ( 2 + 3) * 5 + ( 3 * 7 + 2 + 1 ) + 3";
    printf("%s",parseParanthesis(str));
    return 0;
}
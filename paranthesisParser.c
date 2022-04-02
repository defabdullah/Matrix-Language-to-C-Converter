#include "main.h"


//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){

    //if there is no paranthesis send expression to expression function else paste it

    if(strstr(str,"(")==NULL){
        return expression_parser(str);
    }

    //take it's reverse
    reverseFull=strrev(str);

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
    afterParantModified=strtok(NULL,"");

    //if there is no paranthesis send expression to expression function else paste it
    if(strstr(innerExpression,"(")==NULL){
        innerExpression=expression_parser(innerExpression);
    }
    else{
        innerExpression=parseParanthesis(innerExpression);
    }

    //concatenate string after changing expression with old value
    result=strcat(beforeParant,innerExpression);
    strcat(result,")");
    if(afterParantModified!=NULL){
        result=strcat(result,afterParantModified);
    }

    //if it includes paranthesis then rec. else return
    char *temp=strtok(beforeParant,"(");
    if(strstr(temp,"(") || strstr(temp,")")){
        return parseParanthesis(result);
    }

    return result;
}

char *deleteParanthesis(char *str){
    
    //delete last parant.
    withoutLastParanthesis=strtok(str,")");

    //take it's reverse
    reverseStr=strrev(withoutLastParanthesis);

    //delete open paranth.
    reverse= strtok(reverseStr,"(");

    return strrev(reverse);
}
/*
int main(){
    printf("asf");
    char str[]="tr ( 2 + 3) * 5 + ( 3 * 7 + 2 + 1 ) + 3";
    printf("%s",parseParanthesis(str));
    return 0;
}*/
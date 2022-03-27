#include "paranthesisParser.h"

//reverse function
char* strrev (char *str) {
    if (!str) { return NULL; }

    int len = strnlen(str, 100);
    char*  reverse = malloc( sizeof(char) * len );

    int i;
    for (i = 0; i < len; i++) {
        reverse[i] = str[len - (i+1)];
    }

    reverse[i] = 0;

    return reverse;
}
//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){
    
    //take it's reverse
    reverseStr=strrev(str);

    //create reverse copy string
    reverseCopy = (char *)malloc(strlen(str) + 1);
    strcpy(reverseCopy,reverseStr);

    //string after paranthesis
    afterParantReverse=strtok(reverseCopy,"(");
    afterParant=strrev(afterParantReverse);

    //if there is no paranthesis send expression to expression function
    if(strcmp(afterParantReverse,reverseStr)==0){

        //incomplete ex: op=expression(after)
        return afterParantReverse;
    }

    //string before paranthesis
    beforeParantReverse=strtok(NULL,"");
    beforeParant=strrev(beforeParantReverse);

    //create string after paranthesis
    temp=strtok(afterParant, ")");
    afterParantModified=strtok(NULL,"");

    //concatenate string after changing expression with old value 
    result=strcat(beforeParant,"op");
    if(afterParantModified!=NULL){
        return strcat(result,afterParantModified);
    }

    return result;
}

int main(){
    char str[]="tr(2+3)*5 +(3*7+2+1)+3";
    printf("%s",parseParanthesis(str));
    return 0;
}
#include "main.h"
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

char *deleteParanthesis(char *str){
    
    //delete last parant.
    withoutLastParanthesis=strtok(str,")");

    //take it's reverse
    reverseStr=strrev(withoutLastParanthesis);

    //delete open paranth.
    reverse= strtok(reverseStr,"(");

    return strrev(reverse);
}

char *remove_spaces(char *str)
{   
    char *t;
    int i=0;
    for (t = str; *t != '\0'; t++) {
        //res[i-j] = t;
        if( *t == ' '){
            t++;
        }
        if(*t == '\0'){
            break;
        }
        strncat(res,t,1);  
        i++;
    }
    return res;
}

//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){
    char *token;
    char *copy;
    copy=strdup(str);

    int is_exp=1;
    if(strstr(copy,"(")==NULL || strstr(copy,")")==NULL){
        return str;
    }
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"(") || strcmp(token,")")){
            is_exp=0;
        }
    }
    if(is_exp==1){
        return str;
    }
    //take it's reverse
    reverseFull=strrev(str);
    //return reverseFull;

    //create reverse copy string

    char *reverseCopy=strndup(reverseFull,strlen(reverseFull));

    while((token=strsep(&reverseCopy," "))!=NULL){
        if(strcmp(token,"(")==0){
            strcpy(beforeParantReverse,reverseCopy);
            break;
        }
        strcat(afterParantReverse," ");
        strcat(afterParantReverse,token);
    }

    strcpy(afterParant,strrev(afterParantReverse)); //include expression
    //strcat(space,strdup(afterParant));
    //afterParant=strdup(space);

    //create string after paranthesis
    strcpy(beforeParant,strrev(beforeParantReverse));

    char *temp=strdup(afterParant);
    while((token=strsep(&temp," "))!=NULL){
        if(strcmp(token,")")==0){
            break;
        }
        strcat(innerExpression," ");
        strcat(innerExpression,token);
    }


    //if there is no paranthesis send expression to expression function else paste it
    //if(strstr(innerExpression," ( ")==NULL){
    //   return innerExpression;
    //}
    //concatenate string after changing expression with old value
    strcat(beforeParant," (");
    strcat(beforeParant,"msq");
    strcat(beforeParant,") ");

    
    if(afterParant!=NULL){
        strcat(beforeParant," ");
        strcat(beforeParant,temp);
    }
    return beforeParant;
    //if there is no paranthesis send expression to expression function else paste it
    copy=strdup(result);
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"(")== 0 ||strcmp(token,")")==0){
           return parseParanthesis(result);
        }
    }
   
}




int main(){
    
    char str[]="sqrt ( tr (msq)  * (msq)    ) ";
    printf("%s\n",parseParanthesis(str));
    
    //printf("%s",remove_spaces(" y - x "));
    return (0);
}
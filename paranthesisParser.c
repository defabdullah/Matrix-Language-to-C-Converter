#include "main.h"
/*char* strrev (char *str) {
    if (!str) { return NULL; }

    int len = strnlen(str, 100);
    char*  reverse = malloc( sizeof(char) * len );

    int i;
    for (i = 0; i < len; i++) {
        reverse[i] = str[len - (i+1)];
    }

    reverse[i] = 0;

    return reverse;
}*/

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
    printf("%s\n",str);
    char *token;
    char *copy;
    copy=strdup(str);

    //if there is no paranthesis send expression to expression function else paste it
    int is_exp=1;
    if(strstr(copy,"(")==NULL || strstr(copy,")")==NULL){
        return expression_parser(str);
    }
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"(") || strcmp(token,")")){
            is_exp=0;
        }
    }

    if(is_exp==1){
        return expression_parser(str);
    }

    //take it's reverse
    reverseFull=strrev(str);

    //create reverse copy string
    char *reverseCopy=strndup(reverseFull,strlen(reverseFull));
    char *beforeParant;
    char *beforeParantReverse;
    char *afterParant;
    char *afterParantReverse;

    //merge all
    while((token=strsep(&reverseCopy," "))!=NULL){
        if(strcmp(token,"(")==0){
            strcpy(beforeParantReverse,reverseCopy);
            break;
        }
        strcat(afterParantReverse," ");
        strcat(afterParantReverse,token);
    }

    strcpy(afterParant,strrev(afterParantReverse)); //include expression

    //create string after paranthesis


    strcpy(beforeParant,strrev(beforeParantReverse));
    


    char *temp=strdup(afterParant);
    char *innerExpression;
    while((token=strsep(&temp," "))!=NULL){
        if(strcmp(token,")")==0){
            break;
        }
        strcat(innerExpression," ");
        strcat(innerExpression,token);
    }

    //if there is no paranthesis send expression to expression function else paste it
    char *tempInnerExpression;
    if(strstr(innerExpression," ( ")==NULL){
        tempInnerExpression=expression_parser(innerExpression);
    }
    //concatenate string after changing expression with old value

    strcat(beforeParant," (");
    strcat(beforeParant,tempInnerExpression);
    strcat(beforeParant,") ");


    
    if(afterParant!=NULL){
        strcat(beforeParant," ");
        strcat(beforeParant,temp);
    }

    
    //if there is no paranthesis send expression to expression function else paste it

    copy=strdup(beforeParant);
    
    /*printf("asf");
    printf("%s\n",beforeParant);
    printf("%s",copy);

    exit_program();*/

    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"(")== 0 ||strcmp(token,")")==0){
            printf("%s",beforeParant);
            exit_program();
            return parseParanthesis(beforeParant);
        }
    }



    return expression_parser(beforeParant);
   
}




/*int main(){
    
    char str[]="sqrt ( tr ( y - x ) * ( y - x ) )";
    printf("%s\n",parseParanthesis(str));
    
    //printf("%s",remove_spaces(" y - x "));
    return (0);
}*/
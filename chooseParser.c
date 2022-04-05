#include "main.h"

char *chooseParser(char *str){
    char *copy=strdup(str);
    char *token;
    char before[5000]="";
    int activated=0;
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"choose")){
            activated=1;
        }
        if(activated) {
            char*addToken;
            int stack_number=0;
            while((addToken=strsep(&copy," "))!=NULL){
                strcat(token," ");
                strcat(token,addToken);
                if(strcmp(addToken,"(")==0){
                    stack_number++;
                }
                else if(strcmp(addToken,"(")==0){
                    stack_number--;
                    if(stack_number==0){
                        break;
                    }

                }
            }
            strcat(before,mergeExpressions(token));
            strcat(before,copy);
            return before;
        }
        else{
            strcat(before,token);
            strcat(before," ");
        }

    }

    if(activated==0){
        return str;
    }

    
}
char *mainParser(char *str){

}
char *mergeExpressions(char *str){

}
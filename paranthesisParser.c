#include "main.h"

//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){

    char *token;
    char *prev="";
    char *copy;
    char *tempCopy;
    copy=strdup(str);
    
    //if there is no paranthesis send expression to expression function else paste it
    if(strstr(copy,"(")==NULL || strstr(copy,")")==NULL){
        return expression_parser(str);
    }

    int is_exp=1;
    

    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"(")==0){
            if(prev==NULL || strcmp(prev,"")==0){

                is_exp=0;
                prev=strdup(token);
                continue;
            }

            else if(strcmp(prev,"sqrt")==0||strcmp(prev,"tr")==0||strcmp(prev,"choose")==0){

                tempCopy=strdup(copy);

                if(strcmp(prev,"choose")==0){
                    is_exp=0;
                    /*int is_choose_with_single_tokens=1;
                    for(int i=0;i<7;i++){
                        token=strsep(&copy," ");
                        if( i%2==1 && strcmp(token,",")!=0 ){
                            is_choose_with_single_tokens=0;
                        }
                    }

                    if(strcmp(token=strsep(&copy," "),")")!=0){
                        is_choose_with_single_tokens=0;
                    }

                    if(is_choose_with_single_tokens==1){
                        is_exp=0;
                    }*/

                }

                else if((token=strsep(&copy," "))!=NULL){
                    if(strcmp((token=strsep(&copy," ")),")")!=0){
                        is_exp=0;
                    }
                }
                else{
                    is_exp=0;
                }
                copy=strdup(tempCopy);
            }

            else{
                is_exp=0;
            }

        }  
        prev=strdup(token);
    }


    if(is_exp==1){
        return expression_parser(str);
    }
    
    //create reverse  string

    char *reverseCopy=strrev(str);

    //merge all
    char *tempToken;
    char *firstPrev;
    char *secondPrev;
    
    

    memset(afterParantReverse,0,5000);
    memset(beforeParantReverse,0,5000);

    while((token=strsep(&reverseCopy," "))!=NULL){
        printf("begin:   %s\n",reverseCopy);

        if(strcmp(token,"")==0){
                continue;
        }

        if(strcmp(token,"(")==0){
            printf("if:   %s\n",reverseCopy);

            if(reverseCopy==NULL || strcmp(reverseCopy,"")==0){
                break;
            }
            
            tempCopy=strndup(reverseCopy,strlen(reverseCopy));

            tempToken=strrev(strsep(&tempCopy," "));

            if(tempToken!=NULL && strcmp(tempToken,"")==0 && (strcmp(tempToken,"tr")==0 || strcmp(tempToken,"choose")==0 || strcmp(tempToken,"sqrt")==0)){
                if(strcmp(secondPrev,")")==0){
                    reverseCopy=strndup(tempCopy,strlen(tempCopy));
                }
                else{
                    strcpy(beforeParantReverse,reverseCopy);
                    break;
                }

            }
            else{
                strcpy(beforeParantReverse,reverseCopy);

                break;
            }
        }

        strcat(afterParantReverse," ");
        strcat(afterParantReverse,token);
        
        if(firstPrev!=NULL){
            secondPrev=strdup(firstPrev);
        }
        if(token!=NULL){
            firstPrev=strdup(token);
        }
    }





    memset(beforeParant,0,5000);
    memset(afterParant,0,5000);
    strcpy(beforeParant,strrev(beforeParantReverse));
    strcpy(afterParant,strrev(afterParantReverse)); //include expression




    int is_func=0;
    int is_choose=0;
    
    if(strcmp(beforeParantReverse,"")!=0){
        token=strrev(strtok(beforeParantReverse," "));
        if(token!= NULL && (strcmp(token,"tr")==0 || strcmp(token,"sqrt")==0 || strcmp(token,"choose")==0)){
            is_func=1;
            if(strcmp(token,"choose")==0){
                is_choose=1;
            }
        }
    }

    
    char *temp=strdup(afterParant);

    int stack_num=1;
    char *new;
    memset(innerExpression,0,5000);


    while((new=strsep(&temp," "))!=NULL){
        if(strcmp(new,")")==0){
            stack_num--;
            if(stack_num==0){
                break;
            }
        }
        else if(strcmp(new,"(")==0){
            stack_num++;
        }
        strcat(innerExpression," ");
        strcat(innerExpression,new);
    }
    //if there is no paranthesis send expression to expression function else paste it

    char *tempInnerExpression;
    if(strstr(innerExpression," ( ")==NULL){

        if(is_choose==1){

            tempInnerExpression=chooseParser(innerExpression);
        }
        else{
            tempInnerExpression=expression_parser(innerExpression);
        }
    }

    //concatenate string after changing expression with old value
    if(is_func==1){
        strcat(beforeParant," (");
    }
    strcat(beforeParant," ");
    strcat(beforeParant,tempInnerExpression);
    strcat(beforeParant," ");
    if(is_func==1){
        strcat(beforeParant,") ");
    }

    if(temp!=NULL){
        strcat(beforeParant,temp);
    }

    //if there is no paranthesis send expression to expression function else paste it

    copy=strdup(beforeParant);
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"(")== 0 ||strcmp(token,")")==0){
            return parseParanthesis(beforeParant);
        }
    }
    return expression_parser(beforeParant);
   
}

#include "main.h"

//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){
    
    //printf("%s\n",str);
    char *token;
    char *prev="";
    char *copy;
    char *tempCopy;
    char *tempToken;
    copy=strdup(str);
    
    
    //if there is no paranthesis send expression to expression function else paste it
    if(strstr(copy,"(")==NULL || strstr(copy,")")==NULL){
        //printf("%s\n",str);
        return expression_parser(str);
    }

    int is_exp=1;
    

    while((token=strsep(&copy," "))!=NULL){


        if(strcmp(token,"")==0){
            continue;
        }


        if(strcmp(token,"(")==0){


            if(prev==NULL || strcmp(prev,"")==0){

                is_exp=0;
                prev=strdup(token);
                continue;
            }


            else if(strcmp(prev,"sqrt")==0||strcmp(prev,"tr")==0||strcmp(prev,"choose")==0){

                tempCopy=strdup(copy);
                tempToken=strdup(token);
                if(strcmp(prev,"choose")==0){
                    
                    int is_choose_with_single_tokens=0;
                    for(int i=0;i<7;i++){
                        tempToken=strsep(&copy," ");
                        if( i%2==1 && strcmp(tempToken,",")!=0 ){
                            is_choose_with_single_tokens=1;
                        }
                    }

                    if(strcmp(tempToken=strsep(&copy," "),")")!=0){
                        is_choose_with_single_tokens=1;
                    }

                    if(is_choose_with_single_tokens==1){
                        is_exp=0;
                    }

                }

                else if((tempToken=strsep(&copy," "))!=NULL){
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

    char *reverseCopy=strrev(strdup(trim(str)));
    for(int i=0;i<strlen(reverseCopy);i++){
        printf("token: -%d-\n",reverseCopy[i]);
    }
    

    //merge all
    char *firstPrev;
    char *secondPrev;
    
    
    char *beforeParantReverse;
    char afterParantReverse[5000];
    while((token=strsep(&reverseCopy," "))!=NULL){
        printf("begin:   %s\n",reverseCopy);
        
        //printf("-%s-\n",token);

        if(strcmp(token,"")==0){
                continue;
        }
        if(strcmp(token,"(")==0){

            if(reverseCopy==NULL || strcmp(reverseCopy,"")==0){
                break;
            }
            
            tempCopy=strdup(reverseCopy);

            tempToken=strrev(strtok(tempCopy," "));

            if(tempToken!=NULL && strcmp(tempToken,"")==0 && (strcmp(tempToken,"tr")==0 || strcmp(tempToken,"choose")==0 || strcmp(tempToken,"sqrt")==0)){
                if(strcmp(secondPrev,")")==0){
                    reverseCopy=strdup(tempCopy);
                }
                else{
                    
                    beforeParantReverse=strdup(reverseCopy);
                    break;
                }

            }
            else{
                
                beforeParantReverse=strdup(reverseCopy);

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
    


    char *beforeParant=" ";
    char *afterParant=" ";
    beforeParant=strdup(strrev(beforeParantReverse));
    afterParant=strdup(strrev(afterParantReverse)); //include expression
    int is_func=0;
    int is_choose=0;
    char *beforeParantReverseCopy=strdup(beforeParantReverse);

    if(strcmp(beforeParantReverseCopy,"")!=0){
        

        if(token!= NULL && (strcmp(token,"tr")==0 || strcmp(token,"sqrt")==0 || strcmp(token,"choose")==0)){
            is_func=1;

            if(strcmp(token,"choose")==0){

                is_choose=1;
            }
        }
    }

    int stack_num=1;
    char *new;
    char innerExpression[5000];


    while((new=strsep(&afterParant," "))!=NULL){
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


    //memset(afterParant,0,strlen(afterParant));

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
    memset(innerExpression,0,strlen(innerExpression));

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

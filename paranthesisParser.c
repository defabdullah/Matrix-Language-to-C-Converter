#include "main.h"

//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){
    char *token;
    char *prev="";
    char *copy;
    char *tempCopy;
    char *tempToken;
    copy=strdup(str);    
    
    //if there is no paranthesis send expression to expression function
    if(strstr(copy,"(")==NULL || strstr(copy,")")==NULL){
        return expression_parser(str);
    }

    int is_exp=1;

    //iterates through tokens and decide it needs to parse inner expression or send them directly to expression parser
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        //if it sees open paranthesis it decides to parse it and continue to function
        if(strcmp(token,"(")==0){
            if(prev==NULL || strcmp(prev,"")==0){
                is_exp=0;
                prev=strdup(token);
                continue;
            }
            //if open paranthesis belongs to a special function it controls expression is base case or not
            else if(strcmp(prev,"sqrt")==0||strcmp(prev,"tr")==0||strcmp(prev,"choose")==0){
                tempCopy=strdup(copy);
                tempToken=strdup(token);
                copy=trim(copy);
                //if function is choose it controls 4 base expression
                if(strcmp(prev,"choose")==0){
                    int is_choose_with_single_tokens=0;
                    int iteration=1;
                    while((tempToken=strsep(&copy," "))!=NULL){
                        if(strcmp(tempToken,"")==0){
                            continue;
                        }
                        if(iteration==8){
                            if(strcmp(tempToken,")")!=0){
                                is_choose_with_single_tokens=1;
                            }
                        }
                        else if( (iteration==2 || iteration==4|| iteration==6)  && strcmp(tempToken,",")!=0 ){
                            is_choose_with_single_tokens=1;
                        }
                        else if(iteration>8){
                            is_choose_with_single_tokens=1;
                            break;
                        }
                        iteration++;
                    }
                    
                    if(is_choose_with_single_tokens==1){
                        is_exp=0;
                    }
                }
                //if it is not choose but one of the other special functions it expect base token to send them expression parser
                else if((tempToken=strsep(&copy," "))!=NULL){
                    if(strcmp((token=strsep(&copy," ")),")")!=0){
                        is_exp=0;
                    }
                }
                //if it is not a special function it decide to continue parsing whole expression
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

    //if it doesn't find any expression to parse it sends whole expression to expression parser
    if(is_exp==1){
        return expression_parser(str);
    }
    
    //create reverse  string
    char *reverseCopy=strrev(strdup(trim(str)));

    char *firstPrev;
    char *secondPrev;
    char *beforeParantReverse;
    char afterParantReverse[5000];

    //it starts from reverse to find first open paranthesis and takes before and after of it but in reverse
    while((token=strsep(&reverseCopy," "))!=NULL){
        if(strcmp(token,"")==0){
                continue;
        }
        //it control open paranthesis is belong to special function.
        //If so, it doesn't parse and continue to search another open brackets 
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
    

    //take expression before and after beginning of expression
    char *beforeParant=" ";
    char *afterParant=" ";
    beforeParant=strdup(strrev(beforeParantReverse));
    afterParant=strdup(strrev(afterParantReverse)); //include expression

    memset(afterParantReverse,0,5000);
    int is_func=0;
    int is_choose=0;
    char *beforeParantReverseCopy=strdup(beforeParantReverse);

    //it controls expression is parameter of function
    //if so it adds paranthesis to beginning of expression
    if(strcmp(beforeParantReverseCopy,"")!=0){
        token=strrev(strtok(beforeParantReverseCopy," "));
        if(token!= NULL && (strcmp(token,"tr")==0 || strcmp(token,"sqrt")==0 || strcmp(token,"choose")==0)){
            is_func=1;
            if(strcmp(token,"choose")==0){
                is_choose=1;
            }
        }
    }

    int stack_num=1;
    char *new;
    char innerExpression[5000]="";

    //extract inner expression from after paranthesis
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



    // if expression not include paranthesis it sends to correct parser(choose parser or default expression parser)
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
    if(is_func==1 && is_choose==0){
        strcat(beforeParant," (");
    }
    strcat(beforeParant," ");
    strcat(beforeParant,tempInnerExpression);
    strcat(beforeParant," ");
    if(is_func==1 && is_choose==0){
        strcat(beforeParant,") ");
    }
    if(afterParant!=NULL){
        strcat(beforeParant,afterParant);
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

#include "main.h"

//parse all expression without paranthesis and send them to expression handler function
char *parseParanthesis(char *str){
    printf("copy: %s\n",str);

    char *token;
    char *prev="";
    char *copy;
    char *tempCopy;
    char *tempToken;
    copy=strdup(str);    
    
    //if there is no paranthesis send expression to expression function
    if(strstr(copy,"(")==NULL && strstr(copy,")")==NULL){
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
                        else if((iteration==1 || iteration==3 || iteration==5) && strcmp(tempToken,"tr")==0 && strcmp(tempToken,"sqrt")==0 && strcmp(tempToken,"choose")==0){
                            int parantStack=0;
                            while((tempToken=strsep(&copy," "))!=NULL){
                                if(strcmp(tempToken,"")==0){
                                    continue;
                                }
                                if(strcmp(tempToken,"(")==0){
                                    parantStack++;
                                }
                                else if(strcmp(tempToken,")")==0){
                                    parantStack--;
                                    if(parantStack==0){
                                        break;
                                    }
                                }
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
    char *beforeParantReverse="";
    char afterParantReverse[5000];
    memset(afterParantReverse,0,5000);
    int fullBreak=0;
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

            if(tempToken!=NULL && strcmp(tempToken,"")!=0 && (strcmp(tempToken,"tr")==0 || strcmp(tempToken,"sqrt")==0)){

                if(strcmp(secondPrev,")")!=0){
                    beforeParantReverse=strdup(reverseCopy);
                    fullBreak=1;
                    break;
                }
            }
            else if(tempToken!=NULL && strcmp(tempToken,"")!=0 && strcmp(tempToken,"choose")==0){

                char *chooseTemp=strrev(strdup(afterParantReverse));

                int chooseIteration=2;
                while((tempToken=strsep(&chooseTemp," "))!=NULL){
                    if(strcmp(token,"")==0){
                        continue;
                    }
                    if(chooseIteration==3 || chooseIteration==5 ||chooseIteration==7){
                        if(strcmp(tempToken,",")!=0){
                            beforeParantReverse=strdup(reverseCopy);
                            fullBreak=1;
                            break;
                        }
                    }
                    else if(chooseIteration==2 || chooseIteration==4 ||chooseIteration==6 || chooseIteration==8){
                        if(tempToken!=NULL && strcmp(tempToken,"")!=0 && (strcmp(tempToken,"tr")==0 || strcmp(tempToken,"sqrt")==0)){
                            int parantStack=0;
                            while((tempToken=strsep(&chooseTemp," "))!=NULL){
                                if(strcmp(token,"")==0){
                                    continue;
                                }
                                if(strcmp(token,"(")==0){
                                    parantStack++;
                                }
                                if(strcmp(token,")")==0){
                                    parantStack--;
                                    if(parantStack==0){
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if(chooseIteration==9){
                        if(strcmp(tempToken,")")!=0){
                            beforeParantReverse=strdup(reverseCopy);
                            fullBreak=1;
                            break;
                        }
                    }
                    chooseIteration++;
                }
            }
            else{
                beforeParantReverse=strdup(reverseCopy);
                fullBreak=1;
                break;
            }
        }
        if(fullBreak==1){
            break;
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

    if(beforeParantReverse!=NULL){
        beforeParant=strdup(strrev(beforeParantReverse));
    }
    if(afterParantReverse!=NULL){
        afterParant=strdup(strrev(afterParantReverse)); //include expression
    }


    memset(afterParantReverse,0,5000);
    int is_func=0;
    int is_choose=0;
    char *beforeParantReverseCopy="";
    if(beforeParantReverse!=NULL){
        beforeParantReverseCopy=strdup(beforeParantReverse);

    }

    //it controls expression is parameter of function
    //if so it adds paranthesis to beginning of expression

    if(strcmp(beforeParantReverseCopy,"")!=0){
        token=strrev(strtok(beforeParantReverseCopy," "));
    }
    else{
        char *temp=strdup(afterParant);
        token=strtok(temp," ");
    }
    
    if(token!= NULL && (strcmp(token,"tr")==0 || strcmp(token,"sqrt")==0 || strcmp(token,"choose")==0)){
            is_func=1;
            if(strcmp(token,"choose")==0){
                is_choose=1;
            }
    }

    char *new;
    char innerExpression[5000]="";
    int stack_num=1;
    //extract inner expression from after paranthesis
    int isFirstToken=1;
    while((new=strsep(&afterParant," "))!=NULL){
        if(strcmp(new,"")==0){
            continue;
        }
        if(isFirstToken==1){
            if((strcmp(new,"choose")==0 || strcmp(new,"tr")==0 || strcmp(new,"sqrt")==0) && is_func==1){
                if(strcmp(new,"choose")==0){
                    beforeParant="choose ";
                }
                else if(strcmp(new,"tr")==0){
                    beforeParant="tr ";
                }
                else if(strcmp(new,"sqrt")==0){
                    beforeParant="sqrt ";
                }
                new=strsep(&afterParant," ");
                isFirstToken=0;
                continue;
            }
        }
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

    //control if program exists
    if(stack_num!=0){
        exit_program();
    }


    // if expression not include paranthesis it sends to correct parser(choose parser or default expression parser)
    char *tempInnerExpression;
    if(is_choose==1){
        tempInnerExpression=chooseParser(innerExpression);
    }
    else if(strstr(innerExpression," ( ")==NULL){
        tempInnerExpression=expression_parser(innerExpression);
    }

    //concatenate string after changing expression with old value
    char result[5000];
    memset(result,0,5000);
    strcpy(result,beforeParant);
    if(is_func==1 && is_choose==0){
        strcat(result," (");
    }
    strcat(result," ");

    strcat(result,tempInnerExpression);
    strcat(result," ");

    if(is_func==1 && is_choose==0){
        strcat(result,") ");
    }
    if(afterParant!=NULL){
        strcat(result,afterParant);
    }

    //if there is no paranthesis send expression to expression function else paste it
    copy=strdup(result);
    while((token=strsep(&copy," "))!=NULL){
        if(strcmp(token,"(")== 0 ||strcmp(token,")")==0){

            return parseParanthesis(result);
        }
    }
    return expression_parser(result);
}

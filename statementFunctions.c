#include "main.h"
//initialize the matrix which has form { 1 1  12  5}.
void matrix_initializer(char *line,char *variable_name){
    //fprintf(pOutputFile,"%s","char * token;\ntoken = strtok(line,\" \");\nint i = 0;\nwhile((token=strtok(NULL,\" \")!=NULL)){\n)");
    char * token;
    char* line_copy;
    line_copy= trim(strdup(line));
    int i=1;
    int is_finish=0;
    token=strsep(&line_copy," ");
    // if first token is not numeric then error. Otherwise initialize
    if(is_numeric_string(token)==0){
        exit_program();
    }
    fprintf(pOutputFile,"%s%s%s%s%s","\t*(*",variable_name,")=",token,"; \n");
    // checks other than first token and if they are valid, then initializes.
    while((token=strsep(&line_copy," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        if(strcmp(token,"}")==0){
            is_finish=1;
            continue;
        }
        if(is_finish==1){
            exit_program();
        }else if(is_numeric_string(token)==0){
            exit_program();
        }

        fprintf(pOutputFile,"%s%s%s%d%s%s%s","\t*(*",variable_name,"+",i,")=",token,"; \n");
        i++;
    }
    // if char '}' is not found then error
    if(!is_finish){
        exit_program();
    }
    int firstSize = atoi(first_size(variable_name));
    int secondSize = atoi(second_size(variable_name));
    // if there are more element than it sshould be,then error.
    if(i!=firstSize*secondSize){
        exit_program();
    }
   
}

//assigns value giving specific index. ex. y[ 1 ]= 3.
void assign_value_specified_index(char * line ,char* variable_name){
        //if variable is vector then it moves on. It checks if line has a valid form, if so assigin giving value to index.  
        if(isDeclared(variable_name)==vector){
            int iteration_number=3;
            fprintf(pOutputFile,"%s","\t*(*");fprintf(pOutputFile,"%s",variable_name);
            char * token= strtok(line," ");
            if((is_numeric_string(token)!=1 && isDeclared(token)!=scalar)){
                        exit_program();
            }
            fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
            //traverse token checks string is valid for that form [ scalar  ] = scalar
            while((token=strtok(NULL, " ")) != NULL ){
                    if(iteration_number==3){
                      if(strcmp(token,"]")!=0){
                            exit_program();
                        }
                    }else if(iteration_number==4){
                      if(strcmp(token,"=")!=0){
                            exit_program();
                        }
                    }else if(iteration_number==5){
                      if(is_numeric_string(token)!=1 && isDeclared(token)!=scalar && return_type_of_function(token)!=2){
                            exit_program();
                        }
                        fprintf(pOutputFile,"%s","=");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s",";\n");
                    }else{
                        exit_program();
                    }
                    iteration_number++;
                    }
                if(iteration_number==3){
                    exit_program();
                }
        }else if(isDeclared(variable_name)==matrix){
            int iteration_number=1;
            fprintf(pOutputFile,"%s","\t*(*(");fprintf(pOutputFile,"%s",variable_name);
            char * token= strtok(line," ");
            if((is_numeric_string(token)!=1 && isDeclared(token)!=scalar)){
                         exit_program();
            }
            fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
            //traverse token checks string is valid for that form [ scalar , scalar ] = scalar
            char res[256]="";
            while((token=strtok(NULL, " ")) != NULL ){
                    if(iteration_number==3){
                        if(strcmp(token,"]")!=0){
                            exit_program();
                            break;
                        }
                    }else if(iteration_number==1){
                        if(strcmp(token,",")!=0){
                            exit_program();
                        }
                    }else if(iteration_number==2){
                        if((is_numeric_string(token)!=1 && isDeclared(token)!=scalar)){
                            exit_program();
                        }else{
                            fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
                        }
                    }else if(iteration_number==4){
                        if(strcmp(token,"=")!=0){
                            exit_program();
                        }
                    }else {
                        strcat(res,token);
                        strcat(res," ");
                        /*if(is_numeric_string(token)!=1 && isDeclared(token)!=scalar && return_type_of_function(token)!=2){
                            exit_program();
                        }else{
                            fprintf(pOutputFile,"%s","=");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s",";\n");
                        }*/
                    }
                    iteration_number++;
                }
                if(iteration_number==1){
                    exit_program();
                }
                printf("%s\n",res);
                fprintf(pOutputFile,"%s","=");fprintf(pOutputFile,"%s",parseParanthesis(res));fprintf(pOutputFile,"%s",";\n");
            }

}
//Handle statements which has that form variable = expression. 
//Sends expression to parseParanthesis function and checks variable is Declared 
//and types of variable and expression is compatible (including boundaries). 
void assignment_statement(char * statement,char* variable_name){
    char * token;
    char * line;
    int token_number=1;
    //traverse all tokens
    while((token=strsep(&statement," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        if(token_number==1){
            //if first token has not '=' as a first token, it has to be '[' other wise error. 
            if(strcmp(token,"=")!=0){
                if(strcmp(token,"[")!=0){
                    exit_program();
                }else{
                    // if first token is "[", then it should be assign_value_specified_index and sends to function
                    assign_value_specified_index(trim(strdup(statement)),strdup(variable_name));
                    break;
                }

            }
            if(statement==NULL){
                exit_program();
            }
            line=strdup(statement);
        }else{
            // second token can be either expression or "{". If it is "{" it sends remaining part of the statement to related function 
            if(statement!=NULL){
                    if(strcmp(token,"{")==0){
                        matrix_initializer(statement,variable_name);
                        break;
                    }   
                
            }
            // second token is should be expression.
            // Deteces type of variable and sends expression to parseParanthesis function.
            // prints the result to other file
           
            if(isDeclared(variable_name)==matrix || isDeclared(variable_name)==vector){
               
                char * result=parseParanthesis(line);
                if(return_type_of_function(strdup(result))==2){
                    exit_program();
                }
                char* firstSize= first_size(result);
                char* secondSize= second_size(result);
                char* variable_firstSize = first_size(variable_name);
                char* variable_secondSize = second_size(variable_name);
                if(strcmp(variable_firstSize,firstSize)!=0 || strcmp(variable_secondSize,secondSize)!=0){
                    exit_program();
                }
                
                fprintf(pOutputFile,"%s%s%s%s%s%s%s%s%s","\tmatAssign(",firstSize,",",secondSize, ",*" ,variable_name,",*",result,");\n");

            }else{
                char * result= parseParanthesis(line);
                if(return_type_of_function(strdup(result))==1){
                    exit_program();
                } 
                fprintf(pOutputFile,"%s%s%s","\t",variable_name," =");
                fprintf(pOutputFile,"%s",result);
                fprintf(pOutputFile,"%s",";\n"); 
            }
     
            break;
        }
        token_number++;
    }
}

// handle print( exp ) statements
void print_line(char * line){
    char * print_variable;
    char * token;
    int token_number=1;
    // traverse all tokens sends exp to parseParanthesis function. Also checks if it has a valid form
    while((token=strsep(&line," "))!=NULL){
        if(strcmp(token,"")==0){
                continue;
            }
        if(token_number==1){
            if(strcmp(token,"(")!=0){
                exit_program();
            }
        }else if(token_number==2){
            char temp[256]= "";
            int is_finished=0;
            strcat(temp,token);
            strcat(temp," ");
            while( (token=strsep(&line," "))!=NULL){
                if(strcmp(token,"")==0){
                    continue;
                }
                if(strcmp(token,")")==0){
                    is_finished=1;
                }else if(is_finished==1){
                    exit_program();
                }
                if(is_finished==0){
                    strcat(temp,token);
                    strcat(temp," ");
                }
            }
            if(is_finished==0){
                exit_program();
            }
            print_variable=parseParanthesis(temp);


        }
        token_number++;
    }

    char * print_variable_copy= strdup(print_variable);
    char * print_variable_copy_2= strdup(print_variable);
    // checks type of expresssion and according to type of expression prints to other file necessary function
    if(isDeclared(print_variable)==matrix ||isDeclared(print_variable)==vector ||  is_special_funciton(print_variable)==tr || return_type_of_function(print_variable_copy)==1){
        fprintf(pOutputFile,"%s","\tprintMatrix(");fprintf(pOutputFile,"%s",first_size(print_variable));fprintf(pOutputFile,"%s%s",",",second_size(print_variable));fprintf(pOutputFile,"%s%s",",*",print_variable);fprintf(pOutputFile,"%s",");\n");
    }else if(isDeclared(print_variable)==scalar || return_type_of_function(print_variable_copy_2)==2 ){
        fprintf(pOutputFile,"%s","\tprintScalar(");fprintf(pOutputFile,"%s",print_variable); fprintf(pOutputFile,"%s",");\n");
    }else{
        exit_program();
    }

}
#include "main.h"
void matrix_initializer(char *line,char *variable_name){
    //fprintf(pOutputFile,"%s","char * token;\ntoken = strtok(line,\" \");\nint i = 0;\nwhile((token=strtok(NULL,\" \")!=NULL)){\n)");
    char * token;
    char* line_copy;
    line_copy= trim(strdup(line));
    int i=1;
    int is_finish=0;
    token=strsep(&line_copy," ");
    if(is_numeric_string(token)==0){
        exit_program();
    }
    fprintf(pOutputFile,"%s%s%s%s%s","\t*(*",variable_name,")=",token,"; \n");
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
    if(!is_finish){
        exit_program();
    }
    int firstSize = atoi(first_size(variable_name));
    int secondSize = atoi(second_size(variable_name));
    if(i!=firstSize*secondSize){
        exit_program();
    }
   
}

void assign_value_specified_index(char * line ,char* variable_name){
        if(isDeclared(variable_name)==vector){
            int iteration_number=3;
            fprintf(pOutputFile,"%s","\t*(*");fprintf(pOutputFile,"%s",variable_name);
            char * token= strtok(line," ");
            fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
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
                      if(is_numeric_string(token)!=1){
                            exit_program();
                        }
                        fprintf(pOutputFile,"%s","=");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s",";\n");
                    }else{
                        exit_program();
                    }
                    iteration_number++;
                    }
                if(iteration_number==1){
                    exit_program();
                }
            }else if(isDeclared(variable_name)==matrix){
                int iteration_number=1;
                fprintf(pOutputFile,"%s","\t*(*(");fprintf(pOutputFile,"%s",variable_name);
                char * token= strtok(line," ");
                fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
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
                        if(is_numeric_string(token)!=1){
                            exit_program();
                        }else{
                            fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
                        }
                    }else if(iteration_number==4){
                        if(strcmp(token,"=")!=0){
                            exit_program();
                        }
                    }else if(iteration_number==5){
                        if(is_numeric_string(token)!=1){
                            exit_program();
                        }else{
                            fprintf(pOutputFile,"%s","=");fprintf(pOutputFile,"%s",token);fprintf(pOutputFile,"%s",";\n");
                        }
                    }else{
                        exit_program();
                    }
                    iteration_number++;
                }
                if(iteration_number==1){
                    exit_program();
                }
            }

}

void assignment_statement(char * statement,char* variable_name){
    char * token;
    char * line;
    int token_number=1;
    while((token=strsep(&statement," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        if(token_number==1){
            if(strcmp(token,"=")!=0){
                if(strcmp(token,"[")!=0){
                    exit_program();
                }else{
                    assign_value_specified_index(trim(strdup(statement)),strdup(variable_name));
                    break;
                }

            }
            line=strdup(statement);
        }else{
            if(statement!=NULL){
                    if(strcmp(token,"{")==0){
                        matrix_initializer(statement,variable_name);
                        break;
                    }   
                
            }
           
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


void print_line(char * line){
    char * print_variable;
    char * token;
    int token_number=1;
    
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
            printf("%s\n",token);
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

    /*if(token_number!=4){
        exit_program();
    }*/
    char * print_variable_copy= strdup(print_variable);
    char * print_variable_copy_2= strdup(print_variable);
    if(isDeclared(print_variable)==matrix ||isDeclared(print_variable)==vector ||  is_special_funciton(print_variable)==tr || return_type_of_function(print_variable_copy)==1){
        fprintf(pOutputFile,"%s","\tprintMatrix(");fprintf(pOutputFile,"%s",first_size(print_variable));fprintf(pOutputFile,"%s%s",",",second_size(print_variable));fprintf(pOutputFile,"%s%s",",*",print_variable);fprintf(pOutputFile,"%s",");\n");
    }else if(isDeclared(print_variable)==scalar || return_type_of_function(print_variable_copy_2)==2 ){
        fprintf(pOutputFile,"%s","\tprintScalar(");fprintf(pOutputFile,"%s",print_variable); fprintf(pOutputFile,"%s",");\n");
    }else{
        exit_program();
    }

}
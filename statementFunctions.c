#include "main.h"
void assign_value_specified_index(char * line){
    fprintf(pOutputFile,"%s\n", line);

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
                    assign_value_specified_index(statement);
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
                char* SecondSize= second_size(result);
                fprintf(pOutputFile,"%s%s%s%s%s%s%s%s%s","\tmatAssign(",firstSize,",",SecondSize, ",*" ,variable_name,",*",result,");\n");

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
            while(strcmp(token,")")!=0 && line!=NULL){
                if(token == NULL){
                    exit_program();
                }
                strcat(temp,token);
                strcat(temp," ");
                token=strsep(&line," ");
            }
            strcat(temp,")");
            print_variable=parseParanthesis(temp);

            if(strcmp(token,")")!=0){
                exit_program();
            }
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

void matrix_initializer(char *line,char *variable_name){
    //fprintf(pOutputFile,"%s","char * token;\ntoken = strtok(line,\" \");\nint i = 0;\nwhile((token=strtok(NULL,\" \")!=NULL)){\n)");
    char * token;
    char* line_copy;
    line_copy= strdup(line);
    int i=0;
    token=strsep(&line_copy," ");
    while((token=strsep(&line_copy," "))!=NULL){
        if(strcmp(token,"")==0){
            continue;
        }
        if(strcmp(token,"{")==0){
            continue;
        }
        if(strcmp(token,"}")==0){
            break;
        }
        fprintf(pOutputFile,"%s%s%s%d%s%s%s","\t*(*",variable_name,"+",i,")=",token,"; \n");
        i++;
    }
   
}


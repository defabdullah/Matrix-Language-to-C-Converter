#include "main.h"
void assign_value_specified_index(char * line){
    fprintf(pOutputFile,"%s\n", line);

}

void assignment_statement(char * statement,char* variable_name){
    char * token;
    int token_number=1;
    while((token=strsep(&statement," "))!=NULL){
        if(token_number==1){
            if(strcmp(token,"=")!=0){
                if(strcmp(token,"[")!=0){
                    exit_program();
                }else{
                    assign_value_specified_index(statement);
                    break;
                }

            }
        }else{
            char * statement_copy=strdup(statement);
            char * token;
            token = strtok(statement_copy," "); 
            if(strcmp(token,"{")==0){
                matrix_initializer(statement,variable_name);
                break;
            }
            fprintf(pOutputFile,"%s%s%s","\t",variable_name," =");
            fprintf(pOutputFile,"%s",expression_parser(statement));
            fprintf(pOutputFile,"%s",";\n");      
            break;
        }
        token_number++;
    }

}


void print_line(char * line){
    fprintf(pOutputFile,"\t%s","printScalar");
    char * token;
    int token_number=1;
    while((token=strsep(&line," "))!=NULL){
        if(token_number==1){
            if(strcmp(token,"(")!=0){
                exit_program();
            }else{
                fprintf(pOutputFile,"%s","(");
            }
        }else if(token_number==2){
            fprintf(pOutputFile,"%s",expression_parser(token));

        }else if(token_number==3) {
            if(strcmp(token,")")!=0){
                exit_program();
            }else{
                fprintf(pOutputFile,"%s",");\n");
            }
        }else{
            exit_program();
        }
        token_number++;
        token = strtok(NULL, " ");

    }
    if(token_number!=4){
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
        token = strtok(NULL, " ");
    }
   
}


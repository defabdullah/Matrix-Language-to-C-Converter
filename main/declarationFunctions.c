#include "main.h"
//
void scalar_line(char* line){
    char * token;
    int token_number=1;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        if(token_number==1){
            if(is_alphanumeric_string(token)){
                fprintf(pOutputFile,"%s %s %s","\tdouble",token,";\n");
            }
        }
        token_number++;
    }
    if(token_number!=2){
        exit_program(lineNumber);
    }
}


void vector_line(char* line){
    fprintf(pOutputFile,"%s","\tdouble ");
    char * token;
    int token_number=1;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0 ){
                continue;
        }
        if(token_number==1){
            if(is_alphanumeric(token)==0){
                exit_program(lineNumber);
            }
        }else if(token_number==2){
            if(!strcmp(token,"[")==0){
                exit_program(lineNumber);
            }
        }else if(token_number==3){
            if(is_numeric_string(token)==0){
                exit_program(lineNumber);
            }
        }else if(token_number==4){
            if(!strcmp(token,"]")==0){
                exit_program(lineNumber);
            }
        }
        token_number++;
        
        fprintf(pOutputFile,"%s", token);
    }
    if(token_number!=5){
        exit_program(lineNumber);
    }
    fprintf(pOutputFile,"%s","[1] ;\n");
}

void matrix_line(char* line){
    fprintf(pOutputFile,"%s","\tdouble ");
    char * token;
    int token_number=1;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0 ){
                continue;
        }
        if(token_number==1){
            if(is_alphanumeric(token)==0){
                exit_program(lineNumber);
            }else{
                fprintf(pOutputFile,"%s", token);
            } 
        }else if(token_number==2){
            if(!strcmp(token,"[")==0){
                exit_program(lineNumber);
            }else{
                fprintf(pOutputFile,"%s", token);
            }
        }else if(token_number==3){
            if(is_numeric_string(token)==0){
                exit_program(lineNumber);
            }else{
                fprintf(pOutputFile,"%s", token);
            }
        }else if(token_number==4){
            if(!strcmp(token,",")==0){
                exit_program(lineNumber);
            }else{
                fprintf(pOutputFile,"%s", "]");
                fprintf(pOutputFile,"%s", "[");
            }
        }else if(token_number==5){
            if(is_numeric_string(token)==0){
                exit_program(lineNumber);
            }else{
                fprintf(pOutputFile,"%s", token);
            }
        }else if(token_number==6){
            if(!strcmp(token,"]")==0){
                exit_program(lineNumber);
            }else{
                fprintf(pOutputFile,"%s %s", token,";");
            }
        }
        token_number++;
    }
    if(token_number!=7){
        exit_program(lineNumber);
    }
    fprintf(pOutputFile,"%s","\n");
}

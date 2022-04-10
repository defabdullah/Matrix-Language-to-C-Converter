#include "main.h"
/* 
This file contains functions related declarations. 
*/

// handles scalar declaration. ex: Scalar variableName;
void scalar_line(char* line){
    char * token;
    int token_number=1;
    //traverse all line and if variable name is valid adds variable name to scalarArray and prints to other c file
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        if(token_number==1){
                if(isDeclared(token)!=empty || is_valid_variable_name(token)==0){
                    exit_program();
                }
                fprintf(pOutputFile,"%s %s %s","\tdouble",token,";\n");
                scalarArray[scalarNumber]= token;
                scalarNumber++;
        }
        token_number++;
    }
    if(token_number!=2){
        exit_program();
    }
}

// handles scalar declaration. ex: vector variableName[3] );
void vector_line(char* line){
    fprintf(pOutputFile,"%s","\tdouble ");
    char * token;
    int token_number=1;
    //traverse all line and if variable name and syntax is valid adds variable name to vectorArray and prints to other c file
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0 ){
                continue;
        }
        if(token_number==1){
            if(is_alphanumeric(token)){
                if(isDeclared(token)!=empty || is_valid_variable_name(token)==0){
                    exit_program();
                }
                vectorArray[vectorNumber]=token;
                
            }
            else{
                exit_program();
            }
        }else if(token_number==2){
            if(!strcmp(token,"[")==0){
                exit_program();
            }
        }else if(token_number==3){
            if(is_numeric_string(token)==0){
                exit_program();
            }
            vector_sizes[vectorNumber]=token;
        }else if(token_number==4){
            if(!strcmp(token,"]")==0){
                exit_program();
            }
        }
        token_number++;
        
        fprintf(pOutputFile,"%s", token);
    }
    if(token_number!=5){
        exit_program();
    }
    fprintf(pOutputFile,"%s","[1] ;\n");
    vectorNumber++;


}


// handles matrix declaration. ex: matrix variableName[3][2] );
void matrix_line(char* line){
    fprintf(pOutputFile,"%s","\tdouble ");
    char * token;
    int token_number=1;
     //traverse all line and if variable name and syntax is valid adds variable name to vectorArray and prints to other c file
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0 ){
                continue;
        }
        if(token_number==1){
            if(isDeclared(token)!=empty || is_valid_variable_name(token)==0){
                exit_program();
            }
            fprintf(pOutputFile,"%s", token);
            matrixArray[matrixNumber]=token;
        }else if(token_number==2){
            if(!strcmp(token,"[")==0){
                exit_program();
            }else{
                fprintf(pOutputFile,"%s", token);
            }
        }else if(token_number==3){
            if(is_numeric_string(token)==0){
                exit_program();
            }else{
                matrix_row_sizes[matrixNumber]=token;
                fprintf(pOutputFile,"%s", token);
            }
        }else if(token_number==4){
            if(!strcmp(token,",")==0){
                exit_program();
            }else{
                fprintf(pOutputFile,"%s", "]");
                fprintf(pOutputFile,"%s", "[");
            }
        }else if(token_number==5){
            if(is_numeric_string(token)==0){
                exit_program();
            }else{
                matrix_column_sizes[matrixNumber]=token;
                fprintf(pOutputFile,"%s", token);
            }
        }else if(token_number==6){
            if(!strcmp(token,"]")==0){
                exit_program();
            }else{
                fprintf(pOutputFile,"%s %s", token,";");
            }
        }
        token_number++;
    }
    if(token_number!=7){
        exit_program();
    }
    matrixNumber++;
    fprintf(pOutputFile,"%s","\n");
}
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
                if(isDeclared(token)!=empty || is_valid_variable_name(token)==0){
                    exit_program();
                }
                fprintf(pOutputFile,"%s %s %s","\tdouble",token,";\n");
                scalarArray[scalarNumber]= token;
                scalarNumber++;
            }
        }
        token_number++;
    }
    if(token_number!=2){
        exit_program();
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
            if(is_alphanumeric(token)){
                if(isDeclared(token)!=empty || is_valid_variable_name(token)==0){
                    exit_program();
                }
                vectorArray[vectorNumber]=token;
                vectorNumber++;
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
            if(isDeclared(token)!=empty || is_valid_variable_name(token)==0){
                exit_program();
            }
            fprintf(pOutputFile,"%s", token);
            matrixArray[matrixNumber]=token;
            matrixNumber++; 
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
    fprintf(pOutputFile,"%s","\n");
}

enum types isDeclared(char *str){
    int i;
    for(i=0;i<256;i++){
        if(scalarArray[i]==NULL && vectorArray[i]==NULL && matrixArray[i]==NULL ){
            return empty;
        }
        if(scalarArray[i]!= NULL && strcmp(scalarArray[i],str)==0){
            return scalar;
        }
        else if(vectorArray[i]!= NULL && strcmp(vectorArray[i],str)==0){
            return vector;
        }
        else if(matrixArray[i]!= NULL && strcmp(matrixArray[i],str)==0){
            return matrix;
        }
    }

    return empty;
}
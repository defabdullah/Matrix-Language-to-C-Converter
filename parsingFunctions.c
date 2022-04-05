#include "main.h"

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

int is_alphanumeric(char* s){

    if((*s>='A' && *s<='Z') || (*s>='0' && *s <= '9') || (*s>='a' && *s<='z')){
        return 1;
    }
    else
        return 0;
}
int is_alphanumeric_or_comma(char* s){

    if(is_alphanumeric(s) || (*s=='.')){
        return 1;
    }
    else
        return 0;
}

int is_alphanumeric_string(char* s){
    for(int i =0; i<strlen(s);i++){
        if(!is_alphanumeric(&s[i])){
            return 0;
        }
    }
    return 1;
}

int is_valid_variable_name(char *str){
    if(isdigit(str[0])){
        return 0;
    }
    int i;
    for(i=1;i<strlen(str);i++){
        if(strcmp(&str[i],"_")==0 || is_alphanumeric(&str[i])==0){
            return 0;
        }
    }

    return 1;
}
int has_new_line(char* s){
    for(int i =0; i<strlen(s);i++){
        if((*s>=0 && *s<=32)){
            return 1;
        }
    }
    return 0;
}

int is_numeric_string(char *s){
    for(int i =0; i<strlen(s);i++){
        if(!isdigit(s[i])){
            return 0;
        }
    }
    return 1;
}

char* strrev (char *str) {
    if (!str) { return NULL; }

    int len = strnlen(str, 100);
    char*  reverse = malloc( sizeof(char) * len );

    int i;
    for (i = 0; i < len; i++) {
        reverse[i] = str[len - (i+1)];
    }

    reverse[i] = 0;

    return reverse;
}
int is_matrix_function(char * token){
    if(strcmp(token,"matrixMultiplication")==0 || strcmp(token,"matrixTranspose")==0 || strcmp(token,"matrixSubstraction")==0 || strcmp(token,"matrixSummation")==0 || strcmp(token,"scalarMatrixMultiplication")==0 ){
        return 1;
    }else{
        return 0;
    }
}

int is_scalar_function(char* token){
    if(strcmp(token,"scalarSubstraction")==0 || strcmp(token,"scalarSummation")==0 || strcmp(token,"scalarMultiplication")==0   || strcmp(token,"scalarTranspose")==0 || strcmp(token,"sqrt")==0  ){
        return 1;
    }else{
        return 0;
    }
}

int return_type_of_function(char *token){
    char * token_copy = strdup(token);
    char * first_token = strtok(token_copy,"("); 
    if(is_matrix_function(first_token)==1){
        return 1;
    }else if(is_scalar_function(first_token)){
        return 2;
    }
    return 0;
}

void exit_program(){
    printf("Error (Line %d)",lineNumber);
    exit(1);
}
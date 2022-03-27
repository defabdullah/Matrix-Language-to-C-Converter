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
int is_alphanumeric_string(char* s){
    for(int i =0; i<strlen(s);i++){
        if(!is_alphanumeric(&s[i])){
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

void exit_program(int lineNumber){
    printf("Error (Line %d)",lineNumber);
    exit(1);
}
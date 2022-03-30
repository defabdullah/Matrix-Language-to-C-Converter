#include "main.h"

char special_functionss[][10] = { "tr","choose","sqrt"};
char * special_functions= *special_functionss; 

char  * matrix_initializer(char * line){
        printf("%s\n",line);
        char  result [200] = "{";
        char * token;
        token = strtok(line," ");
        while( (token=strtok(NULL, " ")) != NULL ) {
            char * token_copy;
            token_copy = strdup(token);
            strcat(result,expression_parser(token_copy));
            strcat(result,",");
            printf("%s \n",result);
        }
        return strdup(result);
}




int is_in_chararray(char * token){
    for(int i=0;i<3;i++){
        char *temp= strdup(special_functions);
        if(strcmp(special_functions,token)==0){
            return 1;
        }
        temp+=10;
    }
    return 0;
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

int expression_divider(char* line,char *first,char *second){
    int first_index =0;
    int second_index=0;
    int is_found=0;
    int operator=0;
    char * rev_line=strrev(line);
    for(int i=0;i<strlen(rev_line);i++){
        if((*(rev_line+i)=='+'|| *(rev_line+i)=='-') && is_found==0){
            second[second_index]='\0';
            is_found=1;
            if(*(rev_line+i)=='+'){
                operator=1;
            }else if(*(rev_line+i)=='-'){
                operator=2;
            }
            
        }else if(is_found==0){
            second[second_index]=*(rev_line+i);
            second_index++;
        }else if(is_found==1){
            first[first_index]=*(rev_line+i);
            first_index++;
        }

    }
    second_index=0;
    if(is_found==0){
        memset(first, 0, 256);
        memset(second, 0, 256);
        for(int i=0;i<strlen(rev_line);i++){
            if(*(rev_line+i)=='*' && is_found==0){
                second[second_index]='\0';
                is_found=1;
                operator=3;
            }else if(is_found==0){
                second[second_index]=*(rev_line+i);
                second_index++;
            }else if(is_found==1){
                first[first_index]=*(rev_line+i);
                first_index++;
            }
        }     

    }

    first[first_index]='\0';
    return operator;

}
char* summation(char *first,char* second){
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * first_clean_2 = strdup(first);
    char * second_clean = strdup(second);
    char * second_clean_2 = strdup(second);
    int is_first_in_base=1;
    int is_second_in_base=1;
    ftoken = strtok(first, " ");
    while( (ftoken=strtok(NULL, " ")) != NULL ) {
      is_first_in_base=0;
      break;
    }
    stoken = strtok(second, " ");
    while( (stoken=strtok(NULL, " ")) != NULL ) {
      is_second_in_base=0;
      break;
    }

    char a[256]="(";
    int ftoken_iteration=1;
    int stoken_iteration=1;
    char *ftoken_clean = strtok(first_clean_2," ");

    if(is_in_chararray(ftoken_clean)==1){
        is_first_in_base=1;
        while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
            if(ftoken_iteration==1 && !strcmp(ftoken_clean,"(")==0){
                exit_program(lineNumber);
            }else if(ftoken_iteration==3 && !strcmp(ftoken_clean,")")==0){
                exit_program(lineNumber);
            }else if(ftoken_iteration==4){
                is_first_in_base=0;
            }
            ftoken_iteration++;
        }
    }
    char *stoken_clean = strtok(second_clean_2," ");
    if(is_in_chararray(stoken_clean)==1){
        is_second_in_base=1;
        while( (stoken=strtok(NULL, " ")) != NULL ) {
            if(stoken_iteration==1 && ! strcmp(stoken,"(")){
                exit_program(lineNumber);
            }else if(stoken_iteration==3 && strcmp(stoken,")")){
                exit_program(lineNumber);
            }else if(lineNumber==4){
                is_second_in_base=0;
            }
        }
    }
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char *part = strtok(first_clean," ");
            strcat(a,part);
            while((part=strtok(NULL, " ")) != NULL ){
                strcat(a,part);
            }
            strcat(a,"+");
            char *part2 = strtok(second_clean," ");
                        strcat(a,part2);
            while((part=strtok(NULL, " ")) != NULL ){
                strcat(a,part2);
            }
            strcat(a,")");
            return strtok(a, " ") ;
        }else{

            return summation(first_clean,expression_parser(second_clean));
        }

    }else{
        if(is_second_in_base==1){
            return summation(expression_parser(first_clean),second_clean);
        }else{
            char *f=  expression_parser(first_clean); 
            char *ff= strdup(f);
            char *s=  expression_parser(second_clean);
            return summation(ff,s);
        }
    }
}

char* substraction(char *first,char* second){
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * first_clean_2 = strdup(first);
    char * second_clean = strdup(second);
    char * second_clean_2 = strdup(second);
    int is_first_in_base=1;
    int is_second_in_base=1;
    ftoken = strtok(first, " ");
    while( (ftoken=strtok(NULL, " ")) != NULL ) {
      is_first_in_base=0;
      break;
    }
    stoken = strtok(second, " ");

    while( (stoken=strtok(NULL, " ")) != NULL ) {
      is_second_in_base=0;
      break;
    }
    char a[256]="(";
    int ftoken_iteration=1;
    int stoken_iteration=1;
    char *ftoken_clean = strtok(first_clean_2," ");

    
    if(is_in_chararray(ftoken_clean)==1){
        is_first_in_base=1;
        while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
            if(ftoken_iteration==1 && !strcmp(ftoken_clean,"(")==0){
                exit_program(lineNumber);
            }else if(ftoken_iteration==3 && !strcmp(ftoken_clean,")")==0){
                exit_program(lineNumber);
            }else if(ftoken_iteration==4){
                is_first_in_base=0;
            }
            ftoken_iteration++;
        }
    }
    char *stoken_clean = strtok(second_clean_2," ");
    if(is_in_chararray(stoken_clean)==1){
        is_second_in_base=1;
        while( (stoken=strtok(NULL, " ")) != NULL ) {
            if(stoken_iteration==1 && ! strcmp(stoken,"(")){
                exit_program(lineNumber);
            }else if(stoken_iteration==3 && strcmp(stoken,")")){
                exit_program(lineNumber);
            }else if(lineNumber==4){
                is_second_in_base=0;
            }
        }
    }
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char *part = strtok(first_clean," ");
            strcat(a,part);
            while((part=strtok(NULL, " ")) != NULL ){
                strcat(a,part);
            }
            strcat(a,"-");
            char *part2 = strtok(second_clean," ");
                        strcat(a,part2);
            while((part=strtok(NULL, " ")) != NULL ){
                strcat(a,part2);
            }
            strcat(a,")");
            //printf(": %s \n",a);
            return strdup(a) ;
        }else{

            return substraction(first_clean,expression_parser(second_clean));
        }

    }else{
        if(is_second_in_base==1){
            return substraction(expression_parser(first_clean),second_clean);
        }else{
            char *f=  expression_parser(first_clean); 
            char *ff= strdup(f);
            char *s=  expression_parser(second_clean);
            return substraction(ff,s);
        }
    }
}

char* multiplication(char *first,char* second){
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * first_clean_2 = strdup(first);
    char * second_clean = strdup(second);
    char * second_clean_2 = strdup(second);
    int is_first_in_base=1;
    int is_second_in_base=1;
    ftoken = strtok(first, " ");
    while( (ftoken=strtok(NULL, " ")) != NULL ) {
      is_first_in_base=0;
    }
    stoken = strtok(second, " ");
    while( (stoken=strtok(NULL, " ")) != NULL ) {
      is_second_in_base=0;
    }
    char a[256]="(";
    
    int ftoken_iteration=1;
    int stoken_iteration=1;
    char *ftoken_clean = strtok(first_clean_2," ");
    if(is_in_chararray(ftoken_clean)==1){
        is_first_in_base=1;
        while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
            if(ftoken_iteration==1 && !strcmp(ftoken_clean,"(")==0){
                exit_program(lineNumber);
            }else if(ftoken_iteration==3 && !strcmp(ftoken_clean,")")==0){
                exit_program(lineNumber);
            }else if(ftoken_iteration==4){
                is_first_in_base=0;
            }
            ftoken_iteration++;
        }
    }
    char *stoken_clean = strtok(second_clean_2," ");
    if(is_in_chararray(stoken_clean)==1){
        is_second_in_base=1;
        while( (stoken=strtok(NULL, " ")) != NULL ) {
            if(stoken_iteration==1 && ! strcmp(stoken,"(")){
                exit_program(lineNumber);
            }else if(stoken_iteration==3 && strcmp(stoken,")")){
                exit_program(lineNumber);
            }else if(lineNumber==4){
                is_second_in_base=0;
            }
        }
    }

    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char *part = strtok(first_clean," ");
            strcat(a,part);
            while((part=strtok(NULL, " ")) != NULL ){
                strcat(a,part);
            }
            strcat(a,"*");
            char *part2 = strtok(second_clean," ");
                        strcat(a,part2);
            while((part=strtok(NULL, " ")) != NULL ){
                strcat(a,part2);
            }
            strcat(a,")");
            return strtok(a, " ") ;
        }else{
            return multiplication(strtok(first, " "),expression_parser(second_clean));
        }

    }else{
        if(is_second_in_base==1){
            return multiplication(expression_parser(first_clean),strtok(second, " "));
        }else{
            char *f=  expression_parser(first_clean); 
            char *ff= strdup(f);
            char *s=  expression_parser(second_clean);
            return multiplication(ff,s);
        }
    }

}


char* expression_parser(char *line){
    char  first[256];
    char  second[256];
    memset(first, 0, 256);
    memset(second, 0, 256);

    int operator_type=expression_divider(line,first,second);
    if(operator_type==1){
        return  summation(strrev(first),strrev(second));
    }else if(operator_type==2){
        return substraction(strrev(first),strrev(second));
    }
    else if(operator_type==3){
        return  multiplication(strrev(first),strrev(second));
    }else{
        char * token;
        char * line_copy= strdup(line);
        token = strtok(line_copy," "); 
        if(strcmp(token,"{")==0){
            matrix_initializer(line);
        }
        return line;
    }



}

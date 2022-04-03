#include "main.h"


enum special_functions is_special_funciton(char * token){
    if(strcmp(token,"tr")==0){
        return tr;
    }else if(strcmp(token,"choose")==0){
        return choose;
    }else if(strcmp(token,"sqrt")==0){
        return sqrt;
    }else{
        return none;
    }
}

// takes expression string and divides it into two parts according to precedence.
// returns the type of operator (+,-,*) 
int expression_divider(char* line,char *first_part,char *second_part){
    int first_index =0;
    int second_index=0;
    int is_found=0;
    int operator=0;
    char * rev_line=strrev(line);
    for(int i=0;i<strlen(rev_line);i++){
        if((*(rev_line+i)=='+'|| *(rev_line+i)=='-') && is_found==0){
            second_part[second_index]='\0';
            is_found=1;
            if(*(rev_line+i)=='+'){
                operator=1;
            }else if(*(rev_line+i)=='-'){
                operator=2;
            }
            
        }else if(is_found==0){
            second_part[second_index]=*(rev_line+i);
            second_index++;
        }else if(is_found==1){
            first_part[first_index]=*(rev_line+i);
            first_index++;
        }

    }
    second_index=0;
    if(is_found==0){
        memset(first_part, 0, 256);
        memset(second_part, 0, 256);
        for(int i=0;i<strlen(rev_line);i++){
            if(*(rev_line+i)=='*' && is_found==0){
                second_part[second_index]='\0';
                is_found=1;
                operator=3;
            }else if(is_found==0){
                second_part[second_index]=*(rev_line+i);
                second_index++;
            }else if(is_found==1){
                first_part[first_index]=*(rev_line+i);
                first_index++;
            }
        }     

    }

    first_part[first_index]='\0';
    return operator;

}

char* summation(char *first,char* second){
    char a[2048]="";
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

    int ftoken_iteration=1;
    int stoken_iteration=1;
    char *ftoken_clean = strtok(first_clean_2," ");
    char * first_variable_name;
    enum special_functions  first_function  =is_special_funciton(ftoken_clean);
    char * expOne;
    char * expTwo;
    char * expThree;
    char * expFour;
    char * expOne_second;
    char * expTwo_second;
    char * expThree_second;
    char * expFour_second;
    if(first_function!=none){
        is_first_in_base=1;
        int choose_iterator=1;
        if(first_function==choose){
            while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                if(choose_iterator==1){
                    if(strcmp(ftoken_clean,"(")!=0)
                        exit_program();
                }else if(choose_iterator==2 || choose_iterator==3 || choose_iterator==4){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,ftoken_clean);
                    while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(ftoken_clean,",")==0){
                            break;
                        }
                        strcat(exp,ftoken_clean);
                    }
                    if(choose_iterator==2){
                        expOne=strdup(expression_parser(exp));
                    }else if(choose_iterator==3){
                        expTwo=strdup(expression_parser(exp));
                    }else if(choose_iterator==4){
                        expThree=strdup(expression_parser(exp));
                    }

                }else if(choose_iterator==5){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,ftoken_clean);
                    while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(ftoken_clean,")")==0){
                            break;
                        }
                        strcat(exp,ftoken_clean);
                    }
                    expFour=strdup(expression_parser(exp));
                }else{
                    is_first_in_base=0;
                    break;
                }
                choose_iterator++;
            }
        }else{
            while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                if(ftoken_iteration==1 && !strcmp(ftoken_clean,"(")==0){
                    exit_program();
                }else if(ftoken_iteration==3 && !strcmp(ftoken_clean,")")==0){
                    exit_program();
                }else if(ftoken_iteration==2){
                    if(isDeclared(ftoken_clean)==empty){
                        exit_program();
                    }
                    first_variable_name = ftoken_clean;
                }else if(ftoken_iteration==4){
                    is_first_in_base=0;
                    break;
                }
                ftoken_iteration++;
            }
        }
    }
    char * second_variable_name;
    char *stoken_clean = strtok(second_clean_2," ");
    enum special_functions  second_function  =is_special_funciton(stoken_clean);
    if(second_function!=none){
        is_second_in_base=1;
        int choose_iterator_second=1;
        if(second_function==choose){
            while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                if(choose_iterator_second==1){
                    if(strcmp(stoken_clean,"(")!=0)
                        exit_program();
                }else if(choose_iterator_second==2 || choose_iterator_second==3 || choose_iterator_second==4){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,stoken_clean);
                    while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(stoken_clean,",")==0){
                            break;
                        }
                        strcat(exp,stoken_clean);
                    }
                    if(choose_iterator_second==2){
                        expOne_second=strdup(expression_parser(exp));
                    
                    }else if(choose_iterator_second==3){
                        expTwo_second=strdup(expression_parser(exp));
                    
                    }else if(choose_iterator_second==4){
                        expThree_second=strdup(expression_parser(exp));
                    }

                }else if(choose_iterator_second==5){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,stoken_clean);
                    while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(stoken_clean,")")==0){
                            break;
                        }
                        strcat(exp,stoken_clean);
                    }
                    expFour_second=strdup(expression_parser(exp));
                }else{
                    is_second_in_base=0;
                    break;
                }
                choose_iterator_second++;
            }
        }else{
            while((stoken_clean=strtok(NULL, " ")) != NULL ) {
                if(stoken_iteration==1 && !strcmp(stoken_clean,"(")==0){
                    exit_program();
                }else if(stoken_iteration==2){
                    if(isDeclared(stoken_clean)==empty){
                        exit_program();
                    }
                    second_variable_name = stoken_clean;
                }else if(stoken_iteration==3 && strcmp(stoken_clean,")")){
                    exit_program();
                }else if(stoken_iteration==4){
                    is_second_in_base=0;
                }
                stoken_iteration++;
            }
        }
    }

    if(is_first_in_base==1){
        if(is_second_in_base==1){
            int is_matrix_operation=1;
            char *part = strtok(first_clean," ");
            char* part_copy = strdup(first_clean);
            if(isDeclared(part)==matrix|| isDeclared(part)== vector || is_special_funciton(part)==tr || return_type_of_function(part_copy)==1){
                strcat(a,"matrixSummation(*");

                is_matrix_operation=1;
            }else{
                strcat(a,"scalarSummation(");
            }
            if(first_function==tr){
                strcat(a,"matrixTranspose(sizeof(");  strcat(a,first_variable_name); strcat(a,")/sizeof(");  strcat(a,first_variable_name); strcat(a,"[0]),");
                strcat(a,"sizeof("); strcat(a,first_variable_name); strcat(a,"[0])/sizeof("); strcat(a,first_variable_name); strcat(a,"[0][0]),*");strcat(a,first_variable_name);strcat(a,")");
            }else if(first_function==sqrt){
                strcat(a,"sqrt("); strcat(a,first_variable_name); strcat(a,")");
            }else if(first_function==choose){
                strcat(a,"choose("); strcat(a,expOne); strcat(a,","); strcat(a,expTwo);strcat(a,","); strcat(a,expThree); strcat(a,","); strcat(a,expFour);strcat(a,")");

            }else{
                strcat(a,part);
            }   
            strcat(a,",");
            if(is_matrix_operation){
                strcat(a,"*");
            }
            char *part2 = strtok(second_clean," ");
            if(second_function==tr){
                strcat(a,"matrixTranspose(sizeof(");  strcat(a,second_variable_name); strcat(a,")/sizeof(");  strcat(a,second_variable_name); strcat(a,"[0]),");
                strcat(a,"sizeof("); strcat(a,second_variable_name); strcat(a,"[0])/sizeof("); strcat(a,second_variable_name); strcat(a,"[0][0]),*");strcat(a,second_variable_name);strcat(a,")");
            }else if(second_function==sqrt){
                strcat(a,"sqrt("); strcat(a,second_variable_name); strcat(a,")");
            }else if(second_function==choose){
                strcat(a,"choose("); strcat(a,expOne_second); strcat(a,","); strcat(a,expTwo_second);strcat(a,","); strcat(a,expThree_second); strcat(a,","); strcat(a,expFour_second);strcat(a,")");
            }else{
                strcat(a,part2);
                while((part=strtok(NULL, " ")) != NULL ){
                    strcat(a,part2);
                }
                strcat(a,")");
            }
            return strdup(a) ;
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
    char a[2048]="";
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
    int ftoken_iteration=1;
    int stoken_iteration=1;
    char *ftoken_clean = strtok(first_clean_2," ");
    char * first_variable_name;
    enum special_functions  first_function  =is_special_funciton(ftoken_clean);
    char * expOne;
    char * expTwo;
    char * expThree;
    char * expFour;
    char * expOne_second;
    char * expTwo_second;
    char * expThree_second;
    char * expFour_second;
    if(first_function!=none){
        is_first_in_base=1;
        int choose_iterator=1;
        if(first_function==choose){
            while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                if(choose_iterator==1){
                    if(strcmp(ftoken_clean,"(")!=0)
                        exit_program();
                }else if(choose_iterator==2 || choose_iterator==3 || choose_iterator==4){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,ftoken_clean);
                    while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(ftoken_clean,",")==0){
                            break;
                        }
                        strcat(exp,ftoken_clean);
                    }
                    if(choose_iterator==2){
                        expOne=strdup(expression_parser(exp));
                    }else if(choose_iterator==3){
                        expTwo=strdup(expression_parser(exp));
                    }else if(choose_iterator==4){
                        expThree=strdup(expression_parser(exp));
                    }

                }else if(choose_iterator==5){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,ftoken_clean);
                    while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(ftoken_clean,")")==0){
                            break;
                        }
                        strcat(exp,ftoken_clean);
                    }
                    expFour=strdup(expression_parser(exp));
                }else{
                    is_first_in_base=0;
                    break;
                }
                choose_iterator++;
            }
        }else{
            while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                if(ftoken_iteration==1 && !strcmp(ftoken_clean,"(")==0){
                    exit_program();
                }else if(ftoken_iteration==2){
                    if(isDeclared(ftoken_clean)==empty){
                        exit_program();
                    }
                    first_variable_name = ftoken_clean;
                }else if(ftoken_iteration==3 && !strcmp(ftoken_clean,")")==0){
                    exit_program();
                }else if(ftoken_iteration==4){
                    is_first_in_base=0;
                }
                ftoken_iteration++;
            }
        }
    }
    char *stoken_clean = strtok(second_clean_2," ");
    enum special_functions  second_function  =is_special_funciton(stoken_clean);
    char * second_variable_name;
    if(second_function!=none){
        is_second_in_base=1;
        int choose_iterator_second=1;
        if(second_function==choose){
            while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                if(choose_iterator_second==1){
                    if(strcmp(stoken_clean,"(")!=0)
                        exit_program();
                }else if(choose_iterator_second==2 || choose_iterator_second==3 || choose_iterator_second==4){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,stoken_clean);
                    while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(stoken_clean,",")==0){
                            break;
                        }
                        strcat(exp,stoken_clean);
                    }
                    if(choose_iterator_second==2){
                        expOne_second=strdup(expression_parser(exp));
                    
                    }else if(choose_iterator_second==3){
                        expTwo_second=strdup(expression_parser(exp));
                    
                    }else if(choose_iterator_second==4){
                        expThree_second=strdup(expression_parser(exp));
                    }

                }else if(choose_iterator_second==5){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,stoken_clean);
                    while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(stoken_clean,")")==0){
                            break;
                        }
                        strcat(exp,stoken_clean);
                    }
                    expFour_second=strdup(expression_parser(exp));
                }else{
                    is_second_in_base=0;
                    break;
                }
                choose_iterator_second++;
            }
        }else{
            while( (stoken_clean=strtok(NULL, " ")) != NULL ) {
                if(stoken_iteration==1 && strcmp(stoken_clean,"(")!=0){
                    exit_program();
                }else if(stoken_iteration==2){
                    if(isDeclared(stoken_clean)==empty){
                        exit_program();
                    }
                    second_variable_name = stoken_clean;
                }else if(stoken_iteration==3 && strcmp(stoken_clean,")")!=0){
                    exit_program();
                }else if(stoken_iteration==4){
                    is_second_in_base=0;
                }
                stoken_iteration++;

            }
        }
       
    }
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            int is_matrix_operation=0;
            char *part = strtok(first_clean," ");
            char* part_copy = strdup(first_clean);
            if(isDeclared(part)==matrix|| isDeclared(part)== vector || is_special_funciton(part)==tr || return_type_of_function(part_copy)==1){
                strcat(a,"matrixSubstraction(*");
                is_matrix_operation=1;
            }else{
                strcat(a,"scalarSubstraction(");
            }
            if(first_function==tr){
                strcat(a,"matrixTranspose(sizeof(");  strcat(a,first_variable_name); strcat(a,")/sizeof(");  strcat(a,first_variable_name); strcat(a,"[0]),");
                strcat(a,"sizeof("); strcat(a,first_variable_name); strcat(a,"[0])/sizeof("); strcat(a,first_variable_name); strcat(a,"[0][0]),*");strcat(a,first_variable_name);strcat(a,")");
            }else if(first_function==sqrt){
                strcat(a,"sqrt("); strcat(a,first_variable_name); strcat(a,")");
            }else if(first_function==choose){
                strcat(a,"choose("); strcat(a,expOne); strcat(a,","); strcat(a,expTwo);strcat(a,","); strcat(a,expThree); strcat(a,","); strcat(a,expFour);strcat(a,")");

            }else{
                strcat(a,part);
            }   

            strcat(a,",");
            if(is_matrix_operation){
                strcat(a,",*");
            }
            char *part2 = strtok(second_clean," ");
            if(second_function==tr){
                strcat(a,"matrixTranspose(sizeof(");  strcat(a,second_variable_name); strcat(a,")/sizeof(");  strcat(a,second_variable_name); strcat(a,"[0]),");
                strcat(a,"sizeof("); strcat(a,second_variable_name); strcat(a,"[0])/sizeof("); strcat(a,second_variable_name);  strcat(a,"[0][0]),*");strcat(a,second_variable_name);strcat(a,")");
            }else if(second_function==sqrt){
                strcat(a,"sqrt("); strcat(a,second_variable_name); strcat(a,")");
            }else if(second_function==choose){
                strcat(a,"choose("); strcat(a,expOne_second); strcat(a,","); strcat(a,expTwo_second);strcat(a,","); strcat(a,expThree_second); strcat(a,","); strcat(a,expFour_second);strcat(a,")");
            }else{
                strcat(a,part2);
                while((part=strtok(NULL, " ")) != NULL ){
                    strcat(a,part2);
                }
                strcat(a,")");
            }
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
    char a[2048]="";
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

    int ftoken_iteration=1;
    int stoken_iteration=1;
    char *ftoken_clean = strtok(first_clean_2," ");
    enum special_functions  first_function  =is_special_funciton(ftoken_clean);
    char * first_variable_name;
    char * expOne;
    char * expTwo;
    char * expThree;
    char * expFour;
    char * expOne_second;
    char * expTwo_second;
    char * expThree_second;
    char * expFour_second;
    if(first_function!=none){
        int choose_iterator=1;
        is_first_in_base=1;
        if(first_function==choose){
            while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                if(choose_iterator==1){
                    if(strcmp(ftoken_clean,"(")!=0)
                        exit_program();
                }else if(choose_iterator==2 || choose_iterator==3 || choose_iterator==4){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,ftoken_clean);
                    while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(ftoken_clean,",")==0){
                            break;
                        }
                        strcat(exp,ftoken_clean);
                    }
                    if(choose_iterator==2){
                        expOne=strdup(expression_parser(exp));
                    }else if(choose_iterator==3){
                        expTwo=strdup(expression_parser(exp));
                    }else if(choose_iterator==4){
                        expThree=strdup(expression_parser(exp));
                    }

                }else if(choose_iterator==5){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,ftoken_clean);
                    while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(ftoken_clean,")")==0){
                            break;
                        }
                        strcat(exp,ftoken_clean);
                    }
                    expFour=strdup(expression_parser(exp));
                }else{
                    is_first_in_base=0;
                    break;
                }
                choose_iterator++;
            }
        }else{
            is_first_in_base=1;
            while( (ftoken_clean=strtok(NULL, " "))!= NULL ) {
                if(ftoken_iteration==1 && strcmp(ftoken_clean,"(")!=0){
                    exit_program();
                }else if(ftoken_iteration==2){
                    if((isDeclared(ftoken_clean)==empty)){
                        exit_program();
                }
                first_variable_name = ftoken_clean;
                }else if(ftoken_iteration==3 && strcmp(ftoken_clean,")")!=0){
                    exit_program();
                }else if(ftoken_iteration==4){
                    is_first_in_base=0;
                }
                ftoken_iteration++;
            }
        }
        
    }
    char *stoken_clean = strtok(second_clean_2," ");
    enum special_functions  second_function  =is_special_funciton(stoken_clean);
    char * second_variable_name;
    if(second_function!=none){
        is_second_in_base=1;
        int choose_iterator_second=1;
        if(second_function==choose){
            while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                if(choose_iterator_second==1){
                    if(strcmp(stoken_clean,"(")!=0)
                        exit_program();
                }else if(choose_iterator_second==2 || choose_iterator_second==3 || choose_iterator_second==4){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,stoken_clean);
                    while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(stoken_clean,",")==0){
                            break;
                        }
                        strcat(exp,stoken_clean);
                    }
                    if(choose_iterator_second==2){
                        expOne_second=strdup(expression_parser(exp));
                    
                    }else if(choose_iterator_second==3){
                        expTwo_second=strdup(expression_parser(exp));
                    
                    }else if(choose_iterator_second==4){
                        expThree_second=strdup(expression_parser(exp));
                    }

                }else if(choose_iterator_second==5){
                    char  exp[256] ;
                    memset(exp,0,256);
                    strcat(exp,stoken_clean);
                    while( (stoken_clean=strtok(NULL, " "))!= NULL ) {
                        if(strcmp(stoken_clean,")")==0){
                            break;
                        }
                        strcat(exp,stoken_clean);
                    }
                    expFour_second=strdup(expression_parser(exp));
                }else{
                    is_second_in_base=0;
                    break;
                }
                choose_iterator_second++;
            }
        }else{
            while( (stoken_clean=strtok(NULL, " ")) != NULL ) {
            if(stoken_iteration==1 &&  strcmp(stoken_clean,"(")!=0){
                exit_program();
            }else if(stoken_iteration==2){
                if(isDeclared(stoken_clean)==empty){
                    exit_program();
                }
                second_variable_name = stoken_clean;
            }else if(stoken_iteration==3 && strcmp(stoken_clean,")")!=0){
                exit_program();
            }else if(stoken_iteration==4){
                is_second_in_base=0;
            }
            stoken_iteration++;

            }
        }
        
    }

    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char *part = strtok(first_clean," ");
            char * part_copy=strdup(part);
            if(isDeclared(part)==matrix|| isDeclared(part)== vector || is_special_funciton(part)==tr || return_type_of_function(part_copy)==1){
                strcat(a,"matrixMultiplication(");
            }else{
                strcat(a,"scalarMultiplication(");
            }
            if(first_function==tr){
                strcat(a,"matrixTranspose(sizeof(");  strcat(a,first_variable_name); strcat(a,")/sizeof(");  strcat(a,first_variable_name); strcat(a,"[0]),");
                strcat(a,"sizeof("); strcat(a,first_variable_name); strcat(a,"[0])/sizeof("); strcat(a,first_variable_name);  strcat(a,"[0][0]),*");strcat(a,first_variable_name);strcat(a,")");
            }else if(first_function==sqrt){
                strcat(a,"sqrt("); strcat(a,first_variable_name); strcat(a,")");
            }else if(first_function==choose){
                strcat(a,"choose("); strcat(a,expOne); strcat(a,","); strcat(a,expTwo);strcat(a,","); strcat(a,expThree); strcat(a,","); strcat(a,expFour);strcat(a,")");

            }else{
                strcat(a,part);

            }   
            strcat(a,",");
            char *part2 = strtok(second_clean," ");
            if(second_function==tr){
                strcat(a,"matrixTranspose(sizeof(");  strcat(a,second_variable_name); strcat(a,")/sizeof(");  strcat(a,second_variable_name); strcat(a,"[0]),");
                strcat(a,"sizeof("); strcat(a,second_variable_name); strcat(a,"[0])/sizeof("); strcat(a,second_variable_name);  strcat(a,"[0][0]),*");strcat(a,second_variable_name);strcat(a,")");
            }else if(second_function==sqrt){
                strcat(a,"sqrt("); strcat(a,second_variable_name); strcat(a,")");
            }else if(second_function==choose){
                 strcat(a,"choose("); strcat(a,expOne_second); strcat(a,","); strcat(a,expTwo_second);strcat(a,","); strcat(a,expThree_second); strcat(a,","); strcat(a,expFour_second);strcat(a,")");
            }else{
                strcat(a,part2);
                while((part=strtok(NULL, " ")) != NULL ){
                    strcat(a,part2);
                }
            }
            strcat(a,")");
            return strdup(a) ;
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

// expression_parser is the entrance function. Other functions (summation,multiplication,substraction,expressionn_divider) wont call explixitly.
char* expression_parser(char *line){
    char  first_part[256];
    char  second_part[256];
    memset(first_part, 0, 256);
    memset(second_part, 0, 256);

    
    /* sends expression to expression_divider function and gets the output int the following form <first_part> <operator_type> <second_part>  
       if  operator type is
       1 -> operator is +
       2 -> operator is -
       3 -> operator is *
       0 -> there is not any operator. in this case first_part and second_part variables are meaningless
    */
    int operator_type = expression_divider(line,first_part,second_part);
    // sends first_part and second_part to corresponding functions. Return the final parsed expression string
    if(operator_type==1){
        return  summation(strrev(first_part),strrev(second_part));
    
    }else if(operator_type==2){
        return substraction(strrev(first_part),strrev(second_part));
    
    }else if(operator_type==3){
        return  multiplication(strrev(first_part),strrev(second_part));
    
    }else{
        //char * token;
        //char * line_copy= strdup(line);
        //token = strtok(line_copy," "); 
        /*if(strcmp(token,"{")==0){
            return matrix_initializer(line);
        }*/
        return line;
    }



}

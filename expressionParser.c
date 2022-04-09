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
    char * token;
    int first_index =0;
    int second_index=0;
    int is_found=0;
    int operator=0;
    char * rev_line=strrev(strdup(line));
    char * rev_line_2=strrev(strdup(line));
     while((token=strsep(&rev_line," "))!=NULL){
         if(strcmp(token,"")==0){
             continue;
         }
         if((strcmp(token,"+")==0 || strcmp(token,"-")==0)  && is_found==0){
            is_found=1;
            if(strcmp(token,"+")==0){
                operator=1;
            }else if(strcmp(token,"-")==0){
                 operator=2;
            }
         }else if(is_found==0){
             strcat(second_part," ");
             strcat(second_part,token);
             second_index++;
         }else if(is_found){
            strcat(first_part," ");
            strcat(first_part,token);
            first_index++;
         }
     }
    second_index=0;
    if(is_found==0){
        memset(first_part, 0, 256);
        memset(second_part, 0, 256);
        while((token=strsep(&rev_line_2," "))!=NULL){
            if(strcmp(token,"")==0){
                continue;
            }
            if(strcmp(token,"*")==0  && is_found==0){
                is_found=1;
                operator=3;
            }else if(is_found==0){
                strcat(second_part," ");
                strcat(second_part,token);
                second_index++;
            }else if(is_found){
                strcat(first_part," ");
                strcat(first_part,token);
                first_index++;
            }
        }

    }
    return operator;

}

char* summation(char *first,char* second){
    char a[2048]="";
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * second_clean = strdup(second);
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
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char* first_matrix_first_size;
            char* first_matrix_second_size;
            int is_matrix_operation=0;
            char *part = strtok(first_clean," ");
            char* part_copy = strdup(first_clean);
            int return_type_1=return_type_of_function(part_copy);
            
            if(isDeclared(part)==matrix|| isDeclared(part)== vector || return_type_1==1){
                is_matrix_operation=1;
                first_matrix_first_size = first_size(part);
                first_matrix_second_size = second_size(part);
            }else{
                if(isDeclared(part)==scalar || return_type_1== 2 || is_numeric_string(part)==1){
                    is_matrix_operation=0;

                }else{
                    exit_program();
                }
            }


            int is_matrix_operation_2=0;
            char * second_matrix_first_size;
            char * second_matrix_second_size;
            char * part2 = strtok(second_clean," ");
            char * part2_copy = strdup(second_clean);
            int return_type_2=return_type_of_function(part2_copy);
            
            if(isDeclared(part2)==matrix|| isDeclared(part2)== vector || return_type_2==1){
                if(is_matrix_operation==0){
                    exit_program();
                }
                is_matrix_operation_2=1;
                second_matrix_first_size= first_size(part2);
                second_matrix_second_size=second_size(part2);
                

            }else{
                if(isDeclared(part2)==scalar || return_type_2== 2  ||  is_numeric_string(part2)){
                    if(is_matrix_operation==1){
                        exit_program();
                    }
                    is_matrix_operation_2=0;
                }else{
                    exit_program();
                }
            }
            if(is_matrix_operation==1){
                if(is_matrix_operation_2==1){
                    if(strcmp(first_matrix_first_size,second_matrix_first_size)!=0 || strcmp(first_matrix_second_size,second_matrix_second_size)!=0 ){
                        exit_program();
                    }
                    strcat(a,"matrixSummation(");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,first_matrix_second_size);strcat(a,",*");strcat(a,part);
                    strcat(a,",*");strcat(a,part2);strcat(a,")");
                }else{
                        printf("!!!!!!!!\n");
                }
            }else{
                if(is_matrix_operation_2==0){
                     strcat(a,"scalarSummation(");strcat(a,part);strcat(a,",");strcat(a,part2);strcat(a,")");
                }else{
                    printf("!!!!!!!!\n");
                }
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
            char *ss = strdup(s);
            return summation(ff,ss);
        }
    }
}

char* substraction(char *first,char* second){
    char a[2048]="";
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * second_clean = strdup(second);
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
    
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char* first_matrix_first_size;
            char* first_matrix_second_size;
            int is_matrix_operation=0;
            char *part = strtok(first_clean," ");
            char* part_copy = strdup(first_clean);
            int return_type_1=return_type_of_function(part_copy);
            if(isDeclared(part)==matrix|| isDeclared(part)== vector ||  return_type_1==1){
                is_matrix_operation=1;
                first_matrix_first_size = first_size(part);
                first_matrix_second_size = second_size(part);
            }else{
                if(isDeclared(part)==scalar || return_type_1== 2 || is_numeric_string(part)){
                    is_matrix_operation=0;
                }else{
                    exit_program();
                }
            }
            int is_matrix_operation_2=0;
            char * second_matrix_first_size ;
            char * second_matrix_second_size;
            char *part2 = strtok(second_clean," ");
            char * part2_copy = strdup(second_clean);
            int return_type_2=return_type_of_function(part2_copy);
            if(isDeclared(part2)==matrix|| isDeclared(part2)== vector || return_type_2==1){
                if(is_matrix_operation==0){
                    exit_program();
                }
                is_matrix_operation_2=1;
                second_matrix_first_size= first_size(part2);
                second_matrix_second_size=second_size(part2);
            }else{
                if(isDeclared(part2)==scalar || return_type_2 == 2 ||  is_numeric_string(part2)){
                    if(is_matrix_operation==1){
                        exit_program();
                    }

                    is_matrix_operation_2=0;
                }else{
                    exit_program();
                }
                    
        
            }
            if(is_matrix_operation==1){
                if(is_matrix_operation_2==1){
                    if(strcmp(first_matrix_first_size,second_matrix_first_size)!=0 || strcmp(first_matrix_second_size,second_matrix_second_size)!=0 ){
                        exit_program();
                    }
                    strcat(a,"matrixSubstraction(");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,first_matrix_second_size);strcat(a,",*");strcat(a,part);
                    strcat(a,",*");strcat(a,part2);strcat(a,")");
                }else{
                        printf("!!!!!!!!\n");
                }
            }else{
                if(is_matrix_operation_2==0){
                    strcat(a,"scalarSubstraction(");strcat(a,part);strcat(a,",");strcat(a,part2);strcat(a,")");
                }else{
                    printf("!!!!!!!!\n");
                }
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
    char * second_clean = strdup(second);
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
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char *part = strtok(first_clean," ");
            char * part_copy=strdup(part);
            int return_type=  return_type_of_function(part_copy);
            int is_matrix_operation=0;
            int is_matrix_operation_2=0;
            char* first_matrix_first_size;
            char* first_matrix_second_size;
            if(isDeclared(part)==matrix){ 
                is_matrix_operation=1;
                first_matrix_first_size=matrixFirstSize(part);
                first_matrix_second_size=matrixSecondSize(part);
            }else if(isDeclared(part)==vector){
                is_matrix_operation=1;
                first_matrix_first_size=vectorSize(part);
                first_matrix_second_size="1";
            }else if(return_type==1){
                is_matrix_operation=1;
                first_matrix_first_size= first_size(part);
                first_matrix_second_size=second_size(part);
            }else{
                if(isDeclared(part)==scalar || return_type== 2 || is_numeric_string(part)){
                    is_matrix_operation=0;
                }else{
                    exit_program();
                }
            }
            char *part2 = strtok(second_clean," ");
            char * part2_copy = strdup(part2);
            int return_type_2 = return_type_of_function(part2_copy);
            //char * part2_copy_2 = strdup(second_clean);
            char* second_matrix_first_size;
            char* second_matrix_second_size;
            if(isDeclared(part2)==matrix|| isDeclared(part2)== vector || return_type_2==1){
                    is_matrix_operation_2=1;
                    if(isDeclared(part2)==matrix){
                        second_matrix_first_size=matrixFirstSize(part2);
                        second_matrix_second_size=matrixSecondSize(part2);
                    }else if(isDeclared(part2)==vector){
                        second_matrix_first_size=vectorSize(part2);
                        second_matrix_second_size="1";
                    }else if(return_type_2==1){
                        second_matrix_first_size= first_size(part2);
                        second_matrix_second_size=second_size(part2);
                    }         
            }else{
                if(isDeclared(part2)==scalar || return_type_2== 2 ||  is_numeric_string(part2)){
                    is_matrix_operation_2 = 0;
                }else{
                    exit_program();
                }
            }
            if(is_matrix_operation==1){
                if(is_matrix_operation_2==1){
                    if(strcmp(first_matrix_second_size,second_matrix_first_size)!=0){
                        exit_program();
                    }
                    strcat(a,"matrixMultiplication(");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,second_matrix_second_size);strcat(a,",*");strcat(a,part);
                    strcat(a,",");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,first_matrix_second_size);strcat(a,",*");strcat(a,part2);
                    strcat(a,",");strcat(a,second_matrix_first_size);strcat(a,",");strcat(a,second_matrix_second_size);strcat(a,")");
                }else{
                         strcat(a,"scalarMatrixMultiplication(");strcat(a,first_size(part));strcat(a,",");strcat(a,second_size(part));strcat(a,",");strcat(a,part2);strcat(a,",*");strcat(a,part);strcat(a,")");
                }
            }else{
                if(is_matrix_operation_2==1){
                     strcat(a,"scalarMatrixMultiplication(");strcat(a,first_size(part2));strcat(a,",");strcat(a,second_size(part2));strcat(a,",");strcat(a,part);strcat(a,",*");strcat(a,part2);strcat(a,")");
                }else{
                    strcat(a,"scalarMultiplication(");strcat(a,part);strcat(a,",");strcat(a,part2);strcat(a,")");
                }
            }
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
    //printf("%s\n",line);
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
        char a [1024] = " ";
        char *first_token = strtok(strdup(line)," ");
        enum special_functions  function  =is_special_funciton(first_token);
        if(function!=none){
            int choose_iterator_second=1;
            if(function==choose){
                char * expOne;
                char * expTwo;
                char * expThree;
                char * expFour;
                while( (first_token=strtok(NULL, " "))!= NULL ) {
                    if(choose_iterator_second==1){
                        if(strcmp(first_token,"(")!=0)
                            exit_program();
                    }else if(choose_iterator_second==2 || choose_iterator_second==3 || choose_iterator_second==4){
                        char  exp[256] ;
                        memset(exp,0,256);
                        strcat(exp,first_token);
                        while( (first_token=strtok(NULL, " "))!= NULL ) {
                            if(strcmp(first_token,",")==0){
                                break;
                            }
                            strcat(exp,first_token);
                        }
                        if(choose_iterator_second==2){
                            expOne=strdup(exp);

                        }else if(choose_iterator_second==3){
                            expTwo=strdup(exp);
                    
                        }else if(choose_iterator_second==4){
                            expThree=strdup(exp);
                        }

                    }else if(choose_iterator_second==5){
                        char  exp[256] ;
                        memset(exp,0,256);
                        strcat(exp,first_token);
                        while( (first_token=strtok(NULL, " "))!= NULL ) {
                            if(strcmp(first_token,")")==0){
                                break;
                            }
                            strcat(exp,first_token);
                        }
                        expFour=strdup(exp);
                    }else{
                        exit_program();
                    }
                    choose_iterator_second++;
                }
                strcat(a,"choose("); strcat(a,expOne); strcat(a,","); strcat(a,expTwo);strcat(a,","); strcat(a,expThree); strcat(a,","); strcat(a,expFour);strcat(a,")");
                return strdup(a);
            }else {
            int is_matrix_operation=0;
            int iteration=1;
            char * variable_name;
            char* token;
            token=strsep(&line," ");
            while( (token=strsep(&line," "))!=NULL ) {
                if(strcmp(token,"")==0){
                    continue;
                }
                if(iteration==1 &&  strcmp(token,"(")!=0){
                    exit_program();
                }else if(iteration==2){
                    if(isDeclared(token)==empty && return_type_of_function(strdup(token))==0){
                        exit_program();
                    }else if(isDeclared(token)==matrix ||isDeclared(token)==vector || return_type_of_function(strdup(token))==1){
                        if(function==sqrt){
                            exit_program();
                        }
                        is_matrix_operation=1;
                    }
                    variable_name = token;
                }else if(iteration==3 && strcmp(token,")")!=0){
                    exit_program();
                }else if(iteration==4){
                    exit_program();
                }
                iteration++;

            }
            if(function==tr){
                if(is_matrix_operation==1){
                    strcat(a,"matrixTranspose(");  strcat(a,second_size(variable_name)); strcat(a,",");  strcat(a,first_size(variable_name)); strcat(a,",*");
                    strcat(a,variable_name); strcat(a,")");
                }else{
                    strcat(a,"scalarTranspose(");  strcat(a,variable_name); strcat(a,")");
                }
            }else if(function==sqrt){
                strcat(a,"sqrt("); strcat(a,variable_name); strcat(a,")");
            }
            return strdup(a);
            
            }
        }else{
            int is_vector=0;
            int is_matrix=0;
            if(isDeclared(first_token)==vector){
                is_vector=1;
            }else if(isDeclared(first_token)==matrix){
                is_matrix=1;
            }
            if(is_vector){
                int iteration_number=1;
                char * first_token_copy= strdup(first_token);
                while((first_token=strtok(NULL, " ")) != NULL ){
                    if(iteration_number==1){
                        if(strcmp(first_token,"[")!=0){
                            iteration_number=-1;
                            break;
                        }
                    }else if(iteration_number==2){
                        if(is_numeric_string(first_token)!=1){
                            exit_program();
                        }else{
                            strcat(a,"getValue(");strcat(a,first_size(first_token_copy));strcat(a,",");strcat(a,second_size(first_token_copy));strcat(a,",*");strcat(a,first_token_copy);strcat(a,",");strcat(a,first_token);strcat(a,"-1");strcat(a,",");strcat(a,"0)");
                        }
                    }else if(iteration_number==3){
                        if(strcmp(first_token,"]")!=0){
                            exit_program();
                        }
                    }else{
                        exit_program();
                    }
                    iteration_number++;
                }
                if(iteration_number!=1){
                    return strdup(a);
                }
            }else if(is_matrix){
                int iteration_number=1;
                char * first_token_copy= strdup(first_token);
                while((first_token=strtok(NULL, " ")) != NULL ){
                    if(iteration_number==1){
                        if(strcmp(first_token,"[")!=0){
                            iteration_number=-1;
                            break;
                        }
                    }else if(iteration_number==2){
                        if(is_numeric_string(first_token)!=1){
                            exit_program();
                        }else{
                            strcat(a,"getValue(");strcat(a,first_size(first_token_copy));strcat(a,",");strcat(a,second_size(first_token_copy));strcat(a,",*");strcat(a,first_token_copy);strcat(a,",");strcat(a,first_token);strcat(a,"-1");strcat(a,",");
                        }
                    }else if(iteration_number==3){
                        if(strcmp(first_token,",")!=0){
                            exit_program();
                        }
                    }else if(iteration_number==4){
                        if(is_numeric_string(first_token)!=1){
                            exit_program();
                        }else{
                            strcat(a,first_token);strcat(a,"-1");strcat(a,")");
                        }
                    }else if(iteration_number==5){
                        if(strcmp(first_token,"]")!=0){
                            exit_program();
                        }
                    }else{
                        exit_program();
                    }
                    iteration_number++;
                }
                if(iteration_number!=1){
                    return strdup(a);
                }
            }
            
        }
        return line;
    }
}

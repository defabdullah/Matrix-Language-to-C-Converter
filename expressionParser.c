#include "main.h"

//checks the token if it is one of the speccial function.
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
    //searchs for "+" or "-". If one of them exists divides expression into two part
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
    // if there is no "+" or "-" searches for "*"
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
    //return type of operator.
    //if there is no "+","-","*" then operator is 0.
    return operator;

}

/*
summation, substraction and multiplication do almost same thing for different operators
*/


// takes two string first and second. If both of them are in base form (base form means one token),sums up them
char* summation(char *first,char* second){
    char a[2048]="";
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * second_clean = strdup(second);
    int is_first_in_base=1;
    int is_second_in_base=1;
    ftoken = strtok(first, " ");

    // checks first is in base form
    while( (ftoken=strtok(NULL, " ")) != NULL ) {
      is_first_in_base=0;
      break;
    }
    stoken = strtok(second, " ");
    // checks second is in base form
    while( (stoken=strtok(NULL, " ")) != NULL ) {
      is_second_in_base=0;
      break;
    }
    //if both of them is in base form prints summation to other file
    // else call expression parser recursively
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char* first_matrix_first_size;
            char* first_matrix_second_size;
            int is_matrix_operation=0;
            char *part = strtok(first_clean," ");
            char* part_copy = strdup(first_clean);
            int return_type_1=return_type_of_function(part_copy);
            
            //chhecks first is matrix or scalar
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
            
            // checks second is matrix or vector
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
                    // if both are matrix checks boundries and prints matrix summation
                    if(strcmp(first_matrix_first_size,second_matrix_first_size)!=0 || strcmp(first_matrix_second_size,second_matrix_second_size)!=0 ){
                        exit_program();
                    }
                    strcat(a,"matrixSummation(");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,first_matrix_second_size);strcat(a,",*");strcat(a,part);
                    strcat(a,",*");strcat(a,part2);strcat(a,")");
                }
            }else{
                // if both are scalar checks boundries and prints scalar summation
                if(is_matrix_operation_2==0){
                     strcat(a,"scalarSummation(");strcat(a,part);strcat(a,",");strcat(a,part2);strcat(a,")");
                }
            }

            return strdup(a) ;
        }else{
            
            // if first is in base and second is not, then call summation rcursively
            return summation(first_clean,expression_parser(second_clean));
        }

    }else{
        if(is_second_in_base==1){
           
            // if second is in base and first is not, then call summation rcursively
            return summation(expression_parser(first_clean),second_clean);
        }else{
            // if both of them are not in base, then call summation rcursively
            char *f=  expression_parser(first_clean); 
            char *ff= strdup(f);
            char *s=  expression_parser(second_clean);
            char *ss = strdup(s);
            return summation(ff,ss);
        }
    }
}

// takes two string first and second. If both of them are in base form (base form means one token),substracts second from first
char* substraction(char *first,char* second){
    char a[2048]="";
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * second_clean = strdup(second);
    int is_first_in_base=1;
    int is_second_in_base=1;
    ftoken = strtok(first, " ");
    // checks first is in base form
    while( (ftoken=strtok(NULL, " ")) != NULL ) {
      is_first_in_base=0;
      break;
    }
    stoken = strtok(second, " ");
    // checks second is in base form
    while( (stoken=strtok(NULL, " ")) != NULL ) {
      is_second_in_base=0;
      break;
    }
    //if both of them is in base form prints summation to other file
    // else call expression parser recursively
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            char* first_matrix_first_size;
            char* first_matrix_second_size;
            int is_matrix_operation=0;
            char *part = strtok(first_clean," ");
            char* part_copy = strdup(first_clean);
            int return_type_1=return_type_of_function(part_copy);
            
            //checks first is matrix or scalar
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

            //checks second is matrix or scalar

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

                    // if both are matrix checks boundries and prints matrix substraction

                    if(strcmp(first_matrix_first_size,second_matrix_first_size)!=0 || strcmp(first_matrix_second_size,second_matrix_second_size)!=0 ){
                        exit_program();
                    }
                    strcat(a,"matrixSubstraction(");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,first_matrix_second_size);strcat(a,",*");strcat(a,part);
                    strcat(a,",*");strcat(a,part2);strcat(a,")");
                }
            }else{
                if(is_matrix_operation_2==0){

                    // if both are scalar checks boundries and prints scalar substraction

                    strcat(a,"scalarSubstraction(");strcat(a,part);strcat(a,",");strcat(a,part2);strcat(a,")");
                }
            }
            return strdup(a) ;
        
        }else{
           
            // if first is in base and second is not, then call substraction rcursively
            return substraction(first_clean,expression_parser(second_clean));
        }

    }else{
        if(is_second_in_base==1){
            // if second is in base and first is not, then call substraction rcursively
            return substraction(expression_parser(first_clean),second_clean);
        }else{
             // if both of them are not in base, then call substraction rcursively
            char *f=  expression_parser(first_clean); 
            char *ff= strdup(f);
            char *s=  expression_parser(second_clean);
            return substraction(ff,s);
        }
    }
}

// takes two string first and second. If both of them are in base form (base form means one token),multiplies them
char* multiplication(char *first,char* second){
    char a[2048]="";
    char* ftoken;
    char* stoken;
    char * first_clean = strdup(first);
    char * second_clean = strdup(second);
    int is_first_in_base=1;
    int is_second_in_base=1;
    
    ftoken = strtok(first, " ");
    // checks first is in base form
    while( (ftoken=strtok(NULL, " ")) != NULL ) {
      is_first_in_base=0;
    }
    
    stoken = strtok(second, " ");
    // checks second is in base form
    while( (stoken=strtok(NULL, " ")) != NULL ) {
      is_second_in_base=0;
    }
    
    //if both of them is in base form prints summation to other file
    // else call expression parser recursively
    if(is_first_in_base==1){
        if(is_second_in_base==1){
            
            //checks first is matrix or scalar and if it is matrix assigns  sizes 
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
            char* second_matrix_first_size;
            char* second_matrix_second_size;
            
            //checks if second is matrix or scalar and if it is matrix assigns sizes 
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
                    // if both are matrix checks boundries and prints matrix multipllication
                    if(strcmp(first_matrix_second_size,second_matrix_first_size)!=0){
                        exit_program();
                    }
                    strcat(a,"matrixMultiplication(");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,second_matrix_second_size);strcat(a,",*");strcat(a,part);
                    strcat(a,",");strcat(a,first_matrix_first_size);strcat(a,",");strcat(a,first_matrix_second_size);strcat(a,",*");strcat(a,part2);
                    strcat(a,",");strcat(a,second_matrix_first_size);strcat(a,",");strcat(a,second_matrix_second_size);strcat(a,")");
                }else{
                    // if one of them is scalar and  the other one is matrix , then scalar matrix multiplication.
                    strcat(a,"scalarMatrixMultiplication(");strcat(a,first_size(part));strcat(a,",");strcat(a,second_size(part));strcat(a,",");strcat(a,part2);strcat(a,",*");strcat(a,part);strcat(a,")");
                }
            }else{
                if(is_matrix_operation_2==1){
                    // if one of them is scalar and  the other one is matrix , then scalar matrix multiplication.
                     strcat(a,"scalarMatrixMultiplication(");strcat(a,first_size(part2));strcat(a,",");strcat(a,second_size(part2));strcat(a,",");strcat(a,part);strcat(a,",*");strcat(a,part2);strcat(a,")");
                }else{
                    // if both are scalar checks boundries and prints scalar substraction
                    strcat(a,"scalarMultiplication(");strcat(a,part);strcat(a,",");strcat(a,part2);strcat(a,")");
                }
            }
            return strdup(a) ;
        }else{
            // if first is in base and second is not, then call multiplication rcursively
            return multiplication(strtok(first, " "),expression_parser(second_clean));
        }

    }else{
        if(is_second_in_base==1){
            // if second is in base and first is not, then call multiplication rcursively
            return multiplication(expression_parser(first_clean),strtok(second, " "));
        }else{
            // if both of them are not in base, then call multiplication rcursively
            char *f=  expression_parser(first_clean); 
            char *ff= strdup(f);
            char *s=  expression_parser(second_clean);
            return multiplication(ff,s);
        }
    }

}



// expression_parser is the entrance function. Other functions (summation,multiplication,substraction,expressionn_divider) wont call explixitly.
char* expression_parser(char *linee){
    //printf("%s\n",linee);
    if(linee==NULL){
        exit_program();
    }
    char * line=trim(linee);
    if(strcmp(line,"")==0 || line==NULL){
        exit_program();
    }
    if(is_numeric_string(line)){
        char result[2560]="";
        if(line[0]=='+'||line[0]=='-'){
            char * ntoken;
            while((ntoken=strsep(&line," "))!=NULL){
                if(strcmp(ntoken,"")==0){
                    continue;
                }
                strcat(result,ntoken);
            }
            return strdup(result);
        }else{
            return line;
        }
        
    }
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
        // if there is no "+","-","*", then line comes this code block. 
        char a [1024] = " ";
        char *first_token = strtok(strdup(line)," ");
        enum special_functions  function  =is_special_funciton(first_token);
        // if line is a special types of function(tr, choose, sqrt), goes that block 
        if(function!=none){
            int choose_iterator_second=1;
            // if special function is choose
            if(function==choose){
                char * expOne;
                char * expTwo;
                char * expThree;
                char * expFour;
                // traverse line token by token, and assigns expOne, expTwo, expThree and expoOur.
                // also checks the form 
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
                        if(exp==NULL){
                            exit_program();
                        }
                        if( isDeclared(exp)!=scalar && is_numeric_string(exp)==0 && return_type_of_function(exp)!=2){
                            exit_program();
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
                        if(exp==NULL){
                            exit_program();
                        }
                       if( isDeclared(exp)!=scalar && is_numeric_string(exp)==0 && return_type_of_function(exp)!=2){
                            exit_program();
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
                //printf("%s\n",line);
            // if special function is tr or sqrt, line comes to this block
                int is_matrix_operation=0;
                int iteration=1;
                char * variable_name;
                char* token;
                token=strsep(&line," ");
                //traverse all line token by token and checks if it has a valid form
                while( (token=strsep(&line," "))!=NULL ) {
                    if(strcmp(token,"")==0){
                        continue;
                    }
                    if(iteration==1 &&  strcmp(token,"(")!=0){
                        exit_program();
                    }else if(iteration==2){
                        if(isDeclared(token)==empty && return_type_of_function(strdup(token))==0 && is_numeric_string(token)==0){
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
                if(iteration!=0 && iteration!=4){
                    exit_program();
                }
                //if function is tr or sqrt 
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
            //printf("%s\n",line);
            //if it is not a special functions, comes here. this else block checks if it has for "matrix[scalar,scalar]" or "vector[scalar]".   
            int is_vector=0;
            int is_matrix=0;
            if(isDeclared(first_token)==vector){
                is_vector=1;
            }else if(isDeclared(first_token)==matrix){
                is_matrix=1;
            }
            int iteration_number=1;
            char * first_token_copy= strdup(first_token);
            strsep(&line," ");

            if(is_vector){           
                while((first_token=strsep(&line, " ")) != NULL ){
                    if(iteration_number==1){
                        if(strcmp(first_token,"[")!=0){
                            iteration_number=-1;
                            break;
                        }
                    }else if(iteration_number==2){
                        char tempVectorExpression[5000];
                        int parantStack=0;
                        while((first_token=strsep(&line, " ")) != NULL){
                            if(strcmp(first_token,"")==0){
                                continue;
                            }
                            if(strcmp(first_token,"]")==0 && parantStack==0){
                                fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",parseParanthesis(tempVectorExpression));fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
                                break;
                            }
                            if(strcmp(first_token,"[")==0){
                                parantStack++;
                            }
                            if(strcmp(first_token,"]")==0){
                                parantStack--;
                            }
                            strcat(tempVectorExpression,first_token);
                        }
                        strcat(a,"getValue(");strcat(a,first_size(first_token_copy));strcat(a,",");strcat(a,second_size(first_token_copy));strcat(a,",*");strcat(a,first_token_copy);strcat(a,",");strcat(a,parseParanthesis(first_token));strcat(a,"-1");strcat(a,",");strcat(a,"0)");
                    }
                    iteration_number++;
                }
                if(iteration_number!=-1 && iteration_number!=1 && iteration_number!=4){
                    exit_program();
                }
                if(iteration_number!=-1 && iteration_number!=1){
                    return strdup(a);
                }
            
            }else if(is_matrix){
                //printf("%s\n",line);
                while((first_token=strsep(&line, " ")) != NULL ){
                    //printf("%d tok: %s",iteration_number,first_token);
                    if(iteration_number==1){
                        if(strcmp(first_token,"[")!=0){
                            iteration_number=-1;
                            break;
                        }
                    }else if(iteration_number==2){
                        char tempFirstMatrixExpression[5000];
                        memset(tempFirstMatrixExpression,0,5000);
                        int parantStack=0;
                        while((first_token=strsep(&line, " ")) != NULL){
                            if(strcmp(first_token,"")==0){
                                continue;
                            }
                            if(strcmp(first_token,",")==0 && parantStack==0){
                                fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",parseParanthesis(tempFirstMatrixExpression));fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
                                break;
                            }
                            if(strcmp(first_token,"(")==0){
                                parantStack++;
                            }
                            if(strcmp(first_token,")")==0){
                                parantStack--;
                            }
                            strcat(tempFirstMatrixExpression,first_token);
                        }
                        strcat(a,"getValue(");strcat(a,first_size(first_token_copy));strcat(a,",");strcat(a,second_size(first_token_copy));strcat(a,",*");strcat(a,first_token_copy);strcat(a,",");strcat(a,parseParanthesis(tempFirstMatrixExpression));strcat(a,"-1");strcat(a,",");
                    }else if(iteration_number==3){
                        char tempSecondMatrixExpression[5000];
                        memset(tempSecondMatrixExpression,0,5000);
                        int parantStack=0;
                        while((first_token=strsep(&line, " ")) != NULL){
                            if(strcmp(first_token,"")==0){
                                continue;
                            }
                            if(strcmp(first_token,"]")==0 && parantStack==0){
                                fprintf(pOutputFile,"%s","+");fprintf(pOutputFile,"%s",parseParanthesis(tempSecondMatrixExpression));fprintf(pOutputFile,"%s","-1");fprintf(pOutputFile,"%s",")");
                                break;
                            }
                            if(strcmp(first_token,"[")==0){
                                parantStack++;
                            }
                            if(strcmp(first_token,"]")==0){
                                parantStack--;
                            }
                            strcat(tempSecondMatrixExpression,first_token);
                        }
                        strcat(a,"getValue(");strcat(a,first_size(first_token_copy));strcat(a,",");strcat(a,second_size(first_token_copy));strcat(a,",*");strcat(a,first_token_copy);strcat(a,",");strcat(a,parseParanthesis(tempSecondMatrixExpression));strcat(a,"-1");strcat(a,")");
                   
                    }
                    else{
                        exit_program();
                    }
                    iteration_number++;
                }
                if(iteration_number!=-1 && iteration_number!=1 && iteration_number!=6){
                    exit_program();
                }
                if(iteration_number!=-1 && iteration_number!=1){
                    return strdup(a);
                }
            }
            
        }

        // if line is not one of them above, it should be one token (base case). 
        if(isDeclared(linee)==empty && is_numeric_string(linee)==0 && return_type_of_function(linee)==0){
            exit_program();
        }

        return linee;
    }
}

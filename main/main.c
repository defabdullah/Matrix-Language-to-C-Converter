#include "main.h"
void exit_program(int lineNumber){
    printf("Error (Line %d)",lineNumber);
    exit(1);
}

void printScalarMultiplication(){
    fprintf(pOutputFile,"%s","double scalarMultiplication(double num1,double num2){\n\treturn num1*num2;\n}\n");
}

void printScalarMatrixMultiplication(){
    fprintf(pOutputFile,"%s","double **scalarMatrixMultiplication(double scalar, double **matrix, int row, int column){\n\tdouble **newMatrix;\n\tnewMatrix=(double**)calloc(column,sizeof(double*));\n\tfor(int i=0;i<column;i++){\n\t\tnewMatrix[i]=(double*)calloc(row,sizeof(double));\n\t}\n\n\tfor(int i=0;i<column;i++){\n\t\tfor(int j=0;j<row;j++){\n\t\t\tnewMatrix[i][j]=(scalar*matrix[i][j]);\n\t\t}\n\t}\n\n\treturn newMatrix;\n}\n");
}

void printPrintScalar(){
    fprintf(pOutputFile,"%s","\nvoid printScalar(double value){\n\tif( (int) value ==value){\n\t\tprintf(\"%d\",(int) value);\n\t}else{\n\t\tprintf(\"%0.7f\", value);\n\t} \n}");
}

void printCloseBracket(){
    fprintf(pOutputFile,"%s","}");
}

void print_usual(){
    fprintf(pOutputFile, "%s","#include <stdio.h>\n#include <string.h>\n#include <ctype.h>\n\n");
    fprintf(pOutputFile,"%s","\nvoid printsep(){ \n\tprintf(\"----------\\n\"); \n}\n");
    printScalarMultiplication();
    printScalarMatrixMultiplication();
    printPrintScalar();
    fprintf(pOutputFile,"%s","\n\nint main(){\n\n");

}
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
        if(strcmp(token,"")==0 /*||  has_new_line(token)*/){
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

void printsep(){
    fprintf(pOutputFile,"%s","\n\tprintsep();\n");
}

int main(int argc,char *argv[]){

    char line[256];
    pOutputFile=fopen("file.c","w");
    print_usual();
    if (argc != 2) {
    printf("Give filename as command line argument\n") ;
        pInputFile = fopen(argv[1], "r");
        return 1;
    }
    pInputFile = fopen(argv[1], "r");
    if(pInputFile == NULL) {
        printf("Cannot open %s\n",argv[1]);
        return 1;
    }

    //char extended[512];
    char * token;
    int is_declaratiion=1;
    int is_infor=0;
    char * for_state;

    while( fgets(line,256,pInputFile) != NULL ) {
        lineNumber++;
        // checks if line starts with '#' or line is an empty line, if so continues with next line
        if(line[0]=='#' || line[0]== '\n'){
            continue;
        }
        int cur=0;
        char extended[512];
        for(int i =0; i<strlen(line);i++){
            char as = line[i];
            char *ps = &as;
            if (isspace(as)) {
                extended[cur] = ' ';
                cur++;
                continue;
            }
            if(!is_alphanumeric(ps)){
                extended[cur]=' ';
                cur++;
                extended[cur]=as;
                cur++;
                extended[cur]=' ';
                cur++;
                continue;
                
            }
            extended[cur]=line[i];
            cur++;
        }
        extended[cur]='\0';

        char * pextended = strdup(trim(extended));
        char * pextendeds = strdup(trim(extended));
        
        // declaration while
        while ( is_declaratiion==1 && (token=strsep(&pextended," "))!=NULL ){
            if(strcmp(token,"")==0){
                continue;
            }
            if (strcmp("scalar",token)==0){
                scalar_line(pextended);
                break;
            }else if(strcmp("vector",token)==0){
                vector_line(pextended);
                break;
            }else if(strcmp("matrix",token)==0){
                matrix_line(pextended);
                break;
            }else{
                is_declaratiion=0;
            }
        }

        //statement while
        while((token=strsep(&pextendeds," "))!=NULL && is_declaratiion==0){
            if(strcmp(token,"")==0){
                continue;
            }
            if (strcmp(token,"}")==0){
                if(is_infor==1){
                    is_infor=0;
                    break;
                }
            }
            else if(is_infor==1){
                //print to other file
                break;
            }
            else if(strcmp(token,"for")==0){
                is_infor=1;
                //for function;
                break;
            }else if(strcmp(token,"print")==0){
                //print_line(pextendeds);
                break;
            }else if(strcmp(token,"printsep")==0){
                printsep();
                break;
            }else{
                //asign statement
                break;
            }


        }

        memset(extended, 0, 256);
    }
    printCloseBracket();
    fclose(pOutputFile);
    fclose(pInputFile);

    return(0);
}
#include "main.h"


void print_usual(){
    fprintf(pOutputFile, "%s","#include <stdio.h>\n#include <string.h>\n#include <ctype.h>\n\n");
    fprintf(pOutputFile,"%s","\nvoid printsep(){ \n\tprintf(\"----------\\n\"); \n}");
    fprintf(pOutputFile,"%s","\n\nint main(){\n\n");

}


void printScalarMultiplication(){
    fprintf(pOutputFile,"%s","double scalarMultiplication(double num1,double num2){\n\treturn num1*num2");
}

void printScalarMatrixMultiplication(){
    fprintf(pOutputFile,"%s","double **scalarMatrixMultiplication(double scalar, double **matrix, int row, int column){\ndouble **newMatrix;\n\tnewMatrix=(double**)calloc(column,sizeof(double*));\n\tfor(int i=0;i<column;i++){\n\t\tnewMatrix[i]=(double*)calloc(row,sizeof(double));\n\t}\n\n\tfor(int i=0;i<column;i++){\n\t\tfor(int j=0;j<row;j++){\n\t\t\tnewMatrix[i][j]=(scalar*matrix[i][j]);\n\t}\t\n\t}\n\n\treturn newMatrix;\n\t}");
}

void scalar_line(char* line){
    char * token;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        fprintf(pOutputFile,"%s %s %s","\tdouble",token,";\n");

    }
}

void matrix_line(char* line){
    char * token;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        fprintf(pOutputFile,"%s %s %s","\tdouble",token,";\n");
    }
}


void vector_line(char* line){
    fprintf(pOutputFile,"%s","\tdouble ");
    char * token;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        fprintf(pOutputFile,"%s", token);
    }
    fprintf(pOutputFile,"%s","[1] ;\n");

}


int is_alphanumeric(char* s){

    if((*s>='A' && *s<='Z') || (*s>='0' && *s <= '9') || (*s>='a' && *s<='z')){
        return 1;
    }
    else
        return 0;
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
            if (as == ' ') {
                extended[cur] = as;
                cur++;
                continue;
            }
            if(!is_alphanumeric(ps)){
                extended[cur]=' ';
                cur++;
                if(line[i+1]!=' '){
                    extended[cur]=line[i];
                    cur++;
                    extended[cur]=' ';
                    cur++;
                    continue;
                }
            }
            extended[cur]=line[i];
            cur++;
        }

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
                /*matrix_line(pextended);*/
                break;
            }else{
                is_declaratiion=0;
            }
        }
        //statement line
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
                // print func
                break;
            }else if(strcmp(token,"printsep")==0){
                // print func
                break;
            }else{
                //asign statement
                break;
            }


        }

        memset(extended, 0, 256);
    }



    fclose(pOutputFile);
    fclose(pInputFile);

    return(0);
}
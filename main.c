#include "main.h"

/*
Main file of the project.
reads the .mat file and sends to related function
*/


int main(int argc,char *argv[]){

    char line[256];
    pOutputFile=fopen("file.c","w");
    print_usual();
    //if there is no given filename
    if (argc != 2) {
        printf("Give filename as command line argument\n") ;
        pInputFile = fopen(argv[1], "r");
        return 1;
    }
    pInputFile = fopen(argv[1], "r");
    //if file couldn't open
    if(pInputFile == NULL) {
        printf("Cannot open %s\n",argv[1]);
        return 1;
    }

    char * token;
    int is_declaration=1;
    int is_infor=0;
    scalarNumber=0;
    vectorNumber=0;
    matrixNumber=0;
    //reads the file line by line
    while( fgets(line,256,pInputFile) != NULL ) {
        lineNumber++;
        // checks if line starts with '#' or line is an empty line, if so continues with next line
        if(line[0]=='#' || line[0]== '\n'){
            continue;
        }
        int cur=0;
        char extended[512];
        
        /* adds whitespace before and after characters which is not alpha_numeric. So we can reach token by using strtok and strsep 
            ex: matrix A[4,4]==> matrix A [ 4 , 4 ]
        */

        for(int i =0; i<strlen(line);i++){
            char as = line[i];
            char *ps = &as;
            if (isspace(as)) {
                extended[cur] = ' ';
                cur++;
                continue;
            }
            if(!is_alphanumeric_or_comma(ps)){
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

        // declaration while. Reads first token of each line and decides type then sends line to the corresponding function.
        while ( is_declaration==1 && (token=strsep(&pextended," "))!=NULL ){
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
                is_declaration=0;
            }
        }

        //statement while. Reads first token of each line and decides type of the statement then sends line to the corresponding function.
        while((token=strsep(&pextendeds," "))!=NULL && is_declaration==0){
            if(strcmp(token,"")==0){
                continue;
            }
            // if first token is "}", it should be end of the for loop.Otherwise gives error(exit_program).

            if(is_infor!=0){
                fprintf(pOutputFile,"%s","\t");
                if(is_infor==2){
                    fprintf(pOutputFile,"%s","\t");
                }
            }
            if (strcmp(token,"}")==0){
                if(is_infor==1 || is_infor==2){
                    if(is_infor==2){
                        fprintf(pOutputFile,"%s","}\n");
                        fprintf(pOutputFile,"%s","\t}\n");
                    }else{
                        fprintf(pOutputFile,"%s","}\n");
                    }

                    is_infor=0;
                    break;
                }else{
                    exit_program();
                }
            }else if(strcmp(token,"for")==0){
                //for function;
                if(strstr(pextendeds,",")!=NULL){
                    parseDoubleFor(pextendeds);
                    is_infor=2;
                }
                else{
                    parseSingleFor(pextendeds);
                    is_infor=1;
                }
                break;

            }else if(strcmp(token,"print")==0){
                print_line(pextendeds);
                break;
            }else if(strcmp(token,"printsep")==0){
                printsep();
                break;
            }else{
                enum types type= isDeclared(token);
                if(type==empty){
                    exit_program();
                }
                if(pextendeds==NULL|| trim(pextendeds)==NULL){
                    exit_program();
                }
                assignment_statement(trim(pextendeds),token);
                break;
            }

        }
        memset(extended, 0, 256);
    }
    printCloseBracket();
    //closes files
    fclose(pOutputFile);
    fclose(pInputFile);
    return(0);
}
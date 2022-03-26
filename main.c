#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum types{scalar,vector,matrix};

void print_usual(FILE *pfnew){
    fprintf(pfnew, "%s","#include <stdio.h>\n#include <string.h>\n#include <ctype.h>\n\n");
    fprintf(pfnew,"%s","\nvoid printsep(){ \n\tprintf(\"----------\\n\"); \n}");
    fprintf(pfnew,"%s","\n\nint main(){\n\n");

}

void scalar_line(FILE* pfnew,char* line, int linenumber){
    char * token;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        fprintf(pfnew,"%s %s %s","\tdouble",token,";\n");

    }
}

void matrix_line(FILE* pfnew,char* line, int linenumber){
    char * token;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        fprintf(pfnew,"%s %s %s","\tdouble",token,";\n");
    }
}


void vector_line(FILE* pfnew,char* line, int linenumber){
    fprintf(pfnew,"%s","\tdouble ");
    char * token;
    while ((token=strsep(&line," "))!=NULL ){
        if(strcmp(token,"")==0){
                continue;
        }
        fprintf(pfnew,"%s", token);
    }
    fprintf(pfnew,"%s","[1] ;\n");

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
    FILE *pfnew;
    FILE *fp;

    char line[256];
    pfnew=fopen("file.c","w");
    print_usual(pfnew);
    if (argc != 2) {
    printf("Give filename as command line argument\n") ;
        fp = fopen(argv[1], "r");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Cannot open %s\n",argv[1]);
        return 1;
    }

    int linenumber=0;
    //char extended[512];
    char * token;
    int is_declaratiion=1;
    int is_infor=0;
    char * for_state;
    while( fgets(line,256,fp) != NULL ) {
        linenumber++;
        
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
                scalar_line(pfnew,pextended,linenumber);
                break;
            }else if(strcmp("vector",token)==0){
                vector_line(pfnew,pextended,linenumber);
                break;
            }else if(strcmp("matrix",token)==0){
                /*matrix_line(pfnew,pextended,linenumber);*/
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




    fclose(fp);

    return(1);
}
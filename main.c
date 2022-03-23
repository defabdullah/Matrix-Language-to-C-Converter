#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    FILE *fp;

    char line[256];
  
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

    int currentLine=0;
    //char extended[512];
    char * token;
    while( fgets(line,256,fp) != NULL ) {
        currentLine++;
        
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

        char * pextended = strdup(extended);

        /*while ((token=strsep(&pextended," "))!=NULL){
             printf("%s \n",token);
        }*/
       


        printf("%s \n",trim(extended));
        memset(extended, 0, 256);
    }




    fclose(fp);

    return(1);
}
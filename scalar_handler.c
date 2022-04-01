#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void exit_program(int lineNumber){
    printf("Error (Line %d)",lineNumber);
    exit(1);
}

void scalarHandler(char line[256],int lineNumber){
    FILE *fptr;
    fptr = fopen("scalar_declaration_out_file.txt","w");

    if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);             
    }
    
    char *variable_name=strtok(line," ");
    char *token;

    //control second word exist
    if((token=strtok(NULL," "))!=NULL){
        exit_program(lineNumber);
    }
    

    fprintf(fptr,"double %s;",variable_name);
    fclose(fptr);
}

int main(){
    char arr[]={"count"};
    scalarHandler(arr,4);
    return 0;
}

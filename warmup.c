#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h> 
#include <unistd.h>
#include <fcntl.h>
#define MAX_PATH 4096

void reportProcessors(char *path){

    FILE *fp;

    if ((fp=fopen(path,"r"))==NULL){
        perror(path);
        exit(1);


    }
    int processor=0;
    double cache_size=0;
    char *delim= "\t"; //delim 1 
    char *delim2=" "; // delim to extract value 
    char *endcharVal;
    char *buffer;
    double value=0;


    char lineBuffer[MAX_PATH];
    while(fgets(lineBuffer,sizeof(lineBuffer),fp) !=NULL){
    // printf("%s\n",lineBuffer);
    char *token=strtok(lineBuffer,delim);
    //printf("%s\n,",token);
    errno=0;

    if((token != NULL && strcmp(token, "processor") == 0)){ //get processor number
        token=strtok(NULL,delim2); //gets next token ":"
        token=strtok(NULL,delim2);// gets target token

           // printf("%s\n",token);

        value=strtod(token,&endcharVal);
        if(errno==0){

            processor=value;
            
        }
        else{errno=0;}

    }


    if((token != NULL && strcmp(token, "cache size") == 0)){ //get processor number
       // printf("token is first:%s\n\n",token);

        token=strtok(NULL,delim2);  //gets next token  ":"
        token=strtok(NULL,delim2);  //now get target token 

       // printf("token is then: %s\n\n",token);
        value=strtod(token,&endcharVal);
        if(errno==0){
            cache_size=value;
            token=strtok(NULL,delim2);
            //token=strtok(NULL,delim2);


           // printf("value is: %lf\n\n",cache_size);
            printf("processor %d with a case size of %lf %s\n\n",processor,cache_size,token);
            
        }
        else{errno=0;}


    }

    memset(lineBuffer,0,sizeof(lineBuffer));

    }

    fclose(fp);


}


int main(){
    
    
    reportProcessors("/proc/cpuinfo");
    
    
    
    
    return 0;}
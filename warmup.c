//Anim Ohene

/*The warmup.c file displays the resources consumed by processes. 
It displays the number of processors and the amount of cache in each CPU, 
and the free memory and number of memory buffers. */

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

void reportProcessors(char *path){ // this functions reports 

    FILE *fp;

    if ((fp=fopen(path,"r"))==NULL){ //Initialize stream 
        perror(path);
        exit(1);


    }
    int processor=0;
    double cache_size=0;
    char *delim= "\t"; //delim 1 
    char *delim2=" "; // delim to extract value 
    char *endcharVal;
    double value=0;


    char lineBuffer[MAX_PATH];
    while(fgets(lineBuffer,sizeof(lineBuffer),fp) !=NULL){
    // printf("%s\n",lineBuffer);
    char *token=strtok(lineBuffer,delim);
    //printf("%s\n,",token);
    errno=0;

    if((token != NULL && strcmp(token, "processor") == 0)){ //get processor number of processor and cache size
                                                            // it takes as parameter a path (char *) and returns 
                                                            //void
        token=strtok(NULL,delim2); //gets next token ":"
        token=strtok(NULL,"\n");// gets target token


        value=strtod(token,&endcharVal);
                   

        if (*endcharVal == '\0') {

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
        if (*endcharVal == '\0') {
            cache_size=value;
            token=strtok(NULL,"\n");
            //token=strtok(NULL,delim2);


           // printf("value is: %lf\n\n",cache_size);
            printf("processor %d with a cache size of %lf %s\n\n",processor,cache_size,token);
            
        }
        else{errno=0;}


    }

    memset(lineBuffer,0,sizeof(lineBuffer)); //reset memory of linebuffer

    }

    fclose(fp);


}
void report_meminfo(char *path){ // this function reports the free memory and and buffers.
                                 // it takes as parameter a path (char *)
                                 // this function returns void

 FILE *fp;

    if ((fp=fopen(path,"r"))==NULL){
        perror(path);
        exit(1);


    }
    int freeMemory=0;
    int buffers=0;
    char *delim= ":"; //delim 1 
    char *delim2=" "; // delim to extract value 
    char *endcharVal;
    double value=0;

    char lineBuffer[MAX_PATH];
    errno=0;
 while(fgets(lineBuffer,sizeof(lineBuffer),fp) !=NULL){
     //printf("%s\n",lineBuffer);
     char *token=strtok(lineBuffer,delim);
    //printf("%s\n,",token);
    errno=0;

    if((token != NULL && strcmp(token, "MemFree") == 0)){ //get processor number
        //token=strtok(NULL,delim2);
        while((token)!=NULL){
    


          value=strtod(token,&endcharVal);
          //printf("value is:% lf\n\n",value); 

          if (*endcharVal == '\0') {
            //printf("errno is:%d\n\n",errno);

            //printf("token is:%s and value is:%lf\n\n\n",token,value);
            freeMemory=value;
            char *capacity= strtok(NULL,delim2);
            printf("Free memory %d %s\n",freeMemory,capacity);

          } 

          else{
            value=0;
            errno=0;
          }

          token=strtok(NULL,delim2);
        }

           // printf("%s\n",token);

    

    }


    if((token != NULL && strcmp(token, "Buffers") == 0)){ //get processor number
        //printf("%s\n\n",lineBuffer);
        //printf("%sqwww\n\n",lineBuffer);
       //token= strtok(NULL,delim2);

        while((token)!=NULL){
    


          value=strtod(token,&endcharVal); 

          if (*endcharVal == '\0') {
            buffers=value;
            char *capacity= strtok(NULL,delim2);
            //printf("capacityAMIMMMM: %s\n",capacity);

            printf("Buffers: %d %s\n",buffers,capacity);
          } 

          else{
            value=0;
            errno=0;
          }

          token=strtok(NULL,delim2);
        }

           // printf("%s\n",token);

    

    }

    memset(lineBuffer,0,sizeof(lineBuffer));

    }

    fclose(fp);







}


int main(){
    
    report_meminfo("/proc/meminfo");

    printf("%s","\n\n");

    reportProcessors("/proc/cpuinfo");
    
    
    
    
    return 0;}
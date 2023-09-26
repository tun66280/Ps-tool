#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h> 
#include <unistd.h>
typedef struct{
int p;
int s;
int U;
int S;
int v;
int c;
}options;

void DisplayOptions(options Myoptions){
    printf("Option p is:%d\n",Myoptions.p);
    printf("Option s is:%d\n",Myoptions.s);
    printf("Option U is:%d\n",Myoptions.U);
    printf("Option s is:%d\n",Myoptions.s);
    printf("Option v is:%d\n",Myoptions.v);
    printf("Option c is:%d\n",Myoptions.c);



}

options defaultConstructor(){
options OptionConstructor;    
OptionConstructor.p=0;
OptionConstructor.s=0;
OptionConstructor.U=0;
OptionConstructor.s=0;
OptionConstructor.v=0;
OptionConstructor.c=0;

return OptionConstructor;

    
}


int main(int argc, char **argv){

    options optionStructure=defaultConstructor();


    int options;

    while((options=getopt(argc,argv,"psUSvc"))!=-1){    
        switch(options){
        case 'p':
            optionStructure.p=1;
            break;
        case 's':
            optionStructure.s=1;
            break;
        case 'U':
            optionStructure.U=1;
            break;
        case 'S':
            optionStructure.S=1;
            break;
        case 'v':
            optionStructure.v=1;
            break;

        case 'c':
            optionStructure.c=1;
            break;
        case '?':
            fprintf(stderr,"A wrong option: %c was given as input",optopt);
            break;    

}





}


DisplayOptions(optionStructure);

    return 0;
}



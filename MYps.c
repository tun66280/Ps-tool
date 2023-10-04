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
#define FULL_PATH 1048
typedef struct{
int p;
int s;
int U;
int S;
int v;
int c;
}options;



typedef struct{
int pid;
char state;
unsigned int utime;
unsigned vtime;

}ProcessMetadata;

void DisplayOptions(options Myoptions){
    printf("Option p is:%d\n",Myoptions.p);
    printf("Option s is:%d\n",Myoptions.s);
    printf("Option U is:%d\n",Myoptions.U);
    printf("Option s is:%d\n",Myoptions.s);
    printf("Option v is:%d\n",Myoptions.v);
    printf("Option c is:%d\n",Myoptions.c);



}

int set_Proc_Metadata(ProcessMetadata *Proc){};

uid_t uidcmp(char *path){

FILE *inp;

if((inp=fopen(path,"r"))==NULL){
    perror(path);
    exit(1);
}

char lineBuffer[FULL_PATH];
int value=0;
uid_t Real_Uid=-1;
char *delim1=":";
char *delim2="\t";
char *endcharVal;

while(fgets(lineBuffer,sizeof(lineBuffer),inp)!=NULL){
      //  printf("%s\n\n",lineBuffer);

    char *token=strtok(lineBuffer,delim1);
    //printf("%s\n\n",lineBuffer);

    if(strcmp(token,"Uid")==0){
        printf("%s\n","YESSS!");
       
        token=strtok(NULL,delim2);
        printf("token is:%s\n",token);
        
        value= strtod(token,&endcharVal);
        if(*endcharVal=='\0'){
            Real_Uid=value;

        }





}
memset(lineBuffer,0,sizeof(lineBuffer));

}

return (int)Real_Uid;



}


int procUIDcmp(char *path){
uid_t Uid=getuid();
int procUid=uidcmp(path);
if((int)Uid==procUid){

    return 1;
}
else{
    return 0;
}


}



int isDir(char *path){

struct stat stbuf;

if( stat(path,&stbuf)==0){
   
   if( S_ISDIR(stbuf.st_mode)){
    return 1;

   }

   else{return 0;}

}

else{

    perror("bad path" );

    return 0;
}

}











char  *parseStat_Statm(char *path,int field){
 static char line[FULL_PATH];
FILE *stream;
if((stream=fopen(path,"r"))==NULL){
    perror("stream");
    exit(1);
}

fgets(line,sizeof(line),stream);
printf("%s\n",line);
int count=0;
char *delim=" ";
char *token=strtok(line, delim);

    printf("\n\n\nhere we are %s\n\n",token);
    

while(token!=NULL ){
    if(count==field-1){
    char *target=token;
    fclose(stream);
    printf(" found target %s !!!", target);
    return target;
    }
    count++;

    token=strtok(NULL, delim);

        printf("\n\n\nhere we are %s\n\n",token);

}

    printf("%s","field not present");
    fclose(stream);
    return NULL;

}




void listProcDirectory(){

DIR *stream;
struct dirent **namelist;
char *path="/proc";



int n=scandir(path,&namelist,NULL,alphasort);

if(n==-1){
    perror("scandir");
    exit(1);
}

for (int i=0; i<n;i++){
    if(strcmp(namelist[i]->d_name,".")!=0 && strcmp(namelist[i]->d_name,"..")!=0 ){
    printf("%s\n",namelist[i]->d_name);
    free(namelist[i]);
    }
}
free(namelist);






}




void  parseCMD_Line(char *path){
static char line[FULL_PATH];
FILE *stream;
if((stream=fopen(path,"r"))==NULL){
    perror("stream");
    exit(1);
}

fgets(line,sizeof(line),stream);
printf("%s\n",line);
    
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
    int utime_Field;
    int PID_Field;
    int state_Field;
    int stime_Field;

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
//parseCMD_Line("/proc/1391801/cmdline");

//parseStat_Statm("/proc/1391801/stat",3);

//listProcDirectory();
printf("%d\n",procUIDcmp("/proc/10"));


return 0;
} 

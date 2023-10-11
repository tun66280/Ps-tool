/*MYps.c is used to create an implementation of the ps tool which 
list running processes and displays information about the processes, which 
are specified through options.*/

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
int pathNonExistant(char *path){ // checks if a file doesnt exist. Takes a char * as paramter and returns 1 upon
                                 // a char * as paramter and returns 1 upon 
struct stat stbuf;               // success and 0 upon failure.    

if(stat(path,&stbuf)!=0){

perror(path);
return 1;

}
else{
    return 0;
}

}



char *parseCMD_Line(char *path){ // Gets cmd line from proc. Takes a path as parameter 
static char line[FULL_PATH];     // and returns cmdline of proc/[PID]. Or exits the program of there was
                                 // an error opening the path.   
FILE *stream;
if((stream=fopen(path,"r"))==NULL){
    perror("CMD");
    exit(1);
}

fgets(line,sizeof(line),stream);
char *linecopy=strdup(line);
memset(line,0,sizeof(line));
//printf("%s\n",line);
return linecopy;
    
}




char  *parseStat_Statm(char *path,int field){ // parses the stat and statm files. Takes the a path the either
                                              // stat or statm file and the desired field of the given files, as parameters.
                                              // returns the field value(char *) or NULL if failed.    
 static char line[FULL_PATH];
FILE *stream;
if((stream=fopen(path,"r"))==NULL){
    perror(path);
    exit(1);
}

fgets(line,sizeof(line),stream);
//printf("%s\n",line);
int count=0;
char *delim=" ";
char *token=strtok(line, delim);

   // printf("\n\n\nhere we are %s\n\n",token);
    

while(token!=NULL ){
    if(count==field-1){
    char *target=strdup(token);
    fclose(stream);
    memset(line,0,sizeof(line)); //reset so as to not cause rewritting data and thus undefined behavior
   // printf(" found target %s !!!", target);
    return target;
    }
    count++;

    token=strtok(NULL, delim);

      //  printf("\n\n\nhere we are %s\n\n",token);

}

   // printf("%s","field not present");
    fclose(stream);
    return NULL;

}

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
char *state;
 int utime;
int stime;
int virtualMem;
char *cmdline;


}ProcessMetadata;


ProcessMetadata MetadataConstructor(){
ProcessMetadata MetadataConstructor;    
MetadataConstructor.pid=-1;
MetadataConstructor.state=NULL;
MetadataConstructor.utime=-1;
MetadataConstructor.stime=-1;
MetadataConstructor.virtualMem=-1;
MetadataConstructor.cmdline=NULL;








return MetadataConstructor;

    
}


options defaultConstructor(){
options OptionConstructor;    
OptionConstructor.p=-1;
OptionConstructor.s=-1;
OptionConstructor.U=-1;
OptionConstructor.s=-1;
OptionConstructor.v=-1;
OptionConstructor.c=-1;

return OptionConstructor;

    
}

void DisplayOptions(options Myoptions){ //Displays option struct component values. Takes options struct as parameter
                                        // and returns void.
    printf("Option p is:%d\n",Myoptions.p);
    printf("Option s is:%d\n",Myoptions.s);
    printf("Option U is:%d\n",Myoptions.U);
    printf("Option s is:%d\n",Myoptions.s);
    printf("Option v is:%d\n",Myoptions.v);
    printf("Option c is:%d\n",Myoptions.c);



}


void DisplayProcInfo(ProcessMetadata *Process, options *Myoptions){ //Displays a processes information specified by 
                                                                    // options present or not. Takes a pointer to a ProcessMetadata struct
                                                                    // as well as a pointer to an options struct. Returns void.    
         //   printf("%s","ANIM OHEN!!!!!!!!");


char procpath[FULL_PATH];
snprintf(procpath,sizeof(procpath),"%s%d","/proc/",Process->pid);
if(pathNonExistant(procpath)==1){

    exit(1);

}
    
    printf("%d: ",Process->pid);

    if(Myoptions->s==1){

        printf("%s ",Process->state);
    }

    if(Myoptions->U!=1){
        
        printf("utime=%d ",Process->utime);
    }

    if(Myoptions->S==1){

        printf("stime=%d ",Process->stime);
    }

     if(Myoptions->v==1){

        printf("Virtual Memory=%d ",Process->virtualMem);
    }


    if(Myoptions->c!=1){

        printf("%s", Process->cmdline);
    }

    printf("%s","\n\n");



}

int set_Proc_Metadata(char *Pid, options *optionStructure,  ProcessMetadata *Proc, int recursion){ //this function initialzies the components of a  ProcessMetadata struct 
                                                                                                   // based on the options structs components values. Its takes as parameter    
                                                                                                   // Pid, a pointer to an options strucutre, a pointer to a ProcessMetadata structure
                                                                                                   // and an integer. This function returns 1 upon compeletion 



if(recursion==1){ // manually set PID
    if(optionStructure->p!=1){
    Proc->pid=atoi(Pid);
   // printf("DEbug: %d\n",Proc->pid);
}
}

if(optionStructure->s==1){
    char absPath[FULL_PATH];
    snprintf(absPath,sizeof(absPath),"%s%d%s","/proc/",Proc->pid,"/stat");
    
   // printf("ANIMMMQQQWeare:%s\n\n\n",absPath);
    //printf("%s\n"," State DEBUG");
    Proc->state=parseStat_Statm(absPath,3);
   // printf("State is DEBUG:%s\n",Proc->state);

}

if(optionStructure->U!=1){

    char absPath[FULL_PATH];
    snprintf(absPath,sizeof(absPath),"%s%d%s","/proc/",Proc->pid,"/stat");
    Proc->utime=  atoi( parseStat_Statm(absPath,14));   
}


if(optionStructure->S==1){
    char absPath[FULL_PATH];
    snprintf(absPath,sizeof(absPath),"%s%d%s","/proc/",Proc->pid,"/stat");
    Proc->stime= atoi( parseStat_Statm(absPath,15));
}


if(optionStructure->v==1){
    char absPath[FULL_PATH];
    snprintf(absPath,sizeof(absPath),"%s%d%s","/proc/",Proc->pid,"/statm");
    Proc->virtualMem= atoi( parseStat_Statm(absPath,1));
}

if(optionStructure->c!=1){

     char absPath[FULL_PATH];
    snprintf(absPath,sizeof(absPath),"%s%d%s","/proc/",Proc->pid,"/cmdline");
    Proc->cmdline=parseCMD_Line(absPath);
}

return 1;

}


uid_t getPidUid(char *path){ //gets the UID of a process. Takes as parameter a path specified by a char *
                             // returns UID of the specified process or exits the function if there
                             // was an issue initializing the stream.  

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
       //printf("%s\n","YESSS!");
       
        token=strtok(NULL,delim2);
        //printf("token is:%s\n",token);
        
        value= strtod(token,&endcharVal);
        if(*endcharVal=='\0'){
            Real_Uid=value;

        }





}
memset(lineBuffer,0,sizeof(lineBuffer));

}

return (int)Real_Uid;



}


int procUIDcmp(char *path){ //Compares the current processes UID and a different procesess UID
                            //speicied by getPidUid(char * ) function. returns 1 if UID's of both process are the same
                            // otherwise returns 0 if they are different
uid_t Uid=getuid();
int procUid=getPidUid(path);
if((int)Uid==procUid){

    return 1;
}
else{
    return 0;
}


}

















void dipslayProc(char *Pid, options *optionStructure,  ProcessMetadata *Proc, int recursion){ // This is the Ultiamate abstraction. This function is the ps tool in itself.
                                                                                              // initializes and displays proc information based on specified options. Takes as parameter,
                                                                                              // Pid of a process, a pointer to an options structure, a pointer to a ProcessMetadata structure,
                                                                                              // and an integer. This function returns void.   
if(recursion==0){
   // printf("%s\n\n"," DEBUG 1 WEEEE AREEEE!!!");

set_Proc_Metadata("default", optionStructure, Proc,  recursion);

//printf("%s\n\n","DEBUG 2 AND NOW WEEEE AREEEE!!!");

DisplayProcInfo( Proc,  optionStructure);
}


else{



//DIR *stream;
struct dirent **namelist;
char *path="/proc";



int n=scandir(path,&namelist,NULL,alphasort);

if(n==-1){
    perror("scandir");
    exit(1);
}

for (int i=0; i<n;i++){
    //if(procUIDcmp("/proc/namelist[i]->d_name/status"))
    if(strcmp(namelist[i]->d_name,"1")==0 || strcmp(namelist[i]->d_name,"10")==0 ){
    
//printf("For the others");

    set_Proc_Metadata(namelist[i]->d_name,  optionStructure,   Proc,  recursion);
    DisplayProcInfo( Proc,  optionStructure);

    *Proc=MetadataConstructor();
    free(namelist[i]);
    }
}
free(namelist);




}


}






int main(int argc, char **argv){

     int recursion=1;
    



    options optionStructure=defaultConstructor();

    ProcessMetadata procMetadata=MetadataConstructor();


    int options=0;
    int value=0;
    char *endcharValint;

    while((options=getopt(argc,argv,"p:sUSvc"))!=-1){ 
        char option_char = (char)options; 
   
        switch(options){
        case 'p':
            optionStructure.p=1;
            recursion=0;

            value=strtol(optarg,&endcharValint,10);

            if(*endcharValint=='\0'){
                procMetadata.pid=value;
              //  printf("THEREEEEEEE:%d\n",procMetadata.pid);
            }

            else{
                fprintf(stderr,"Error! No argument was specified for the option %c \n",option_char);
                exit(1);
            }
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
            if(optopt=='p'){
                fprintf(stderr, " error, no argument was speciifeied for option: %c \n",optopt);
                exit(1);
            }
            else{
            fprintf(stderr,"A wrong option: %c was given as input. Or option requires an argument not specified\n",optopt);
            exit(1);
            }
        default:
            break;        

}





}


//printf("%s\n\n","ANIM IT WORKSSSSS");

dipslayProc("default",   &optionStructure,   &procMetadata,  recursion);

//printf("%d\n",procUIDcmp("/proc/3478347/status"));

printf("\ncmd is :%s",procMetadata.cmdline);

//printf("%s", parseCMD_Line("/proc/1/cmdline"));
return 0;
} 


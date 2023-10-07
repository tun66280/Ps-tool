# Anim Ohene
# project-1-F23
# The /PROC File System  

# Section 1: Comple and Run
To compile and run the program simply use the make command. If you run make with no arguments then it will create an excecutable file called Main from the object files created. Now, if you wish the run the program you must specify the "Run" target after entering the make command. Due to the nature of our program, you can specify the the command line arguments you wish to enable at the time of execution. To do this, enter in your command line: 
make Run ARGS= "arg1 arg2 argN"   where arg1 - the Nth argument specifies the options you wish to enable.



# Section 2: Design and Implementation

The creation of all the files in my project followed the same approach. Whether we are dealing with the virtual file system or the regular filesystem, the strategy for interacting with such systems remain the same. we must declare a stream, initialize it  with with fopen()[files] or opendir()[directories], processes a given file or directory , then close the stream. It is the understanding of these fundemental actions that can enable one to interact with filesystem, and which lead to the success of such a project. The project consist of 3 files. MYps.c, Makefile, and warmup.c. 

 # Section 2.1: MYps.c
MYps.c was used to create an implementation of the ps tool which list running processes and displays information about the processes, which are specified through options.

# Section 2.1.2: parseCMD_Line function
The char *parseCMD_Line(char *path) function extracts the contents of the 
/proc/[PID]/cmdline file. This function takes /proc/[PID]/cmdline as a parameter and returns a pointer to a copy of the buffer from which we read the cmdline file into. This function is used in our int set_Proc_Metadata(char *Pid, options *optionStructure,  ProcessMetadata *Proc, int recursion) function to initialize  our cmdline field in a record for a processMetadata structure. 

# Section 2.1.3: parseStat_Statm function
The char  *parseStat_Statm(char *path,int field) is a function used to parse the stat and statm virtual file in the the proc virtual file system and extract the contents of a specified field. This function takes /proc/[PID]/stat or /proc/[PID]/statm  as a parameter and returns a pointer to a copy of the buffer from which we read the statm/stat files into. This function is used in our int set_Proc_Metadata(char *Pid, options *optionStructure,  ProcessMetadata *Proc, int recursion) function to initialize  our state, utime, stime, and virtualMem fields in a a record for a processMetadata structure

# Sectin 2.1.4: pathNonExistant function
The int pathNonExistant(char *path) function is very simple. It is used to discern whether a given path exist.It simply takes a path as a parameter and returns 1 for if it doesnt exist and 0 for if it exist. it is used in the void DisplayProcInfo(ProcessMetadata *Process, options *Myoptions) function to immediately dictate whether to exit a the function or continue, based on the fact of if the path exist or not. 



# Sectin 2.1.5:  MetadataConstructor function
the ProcessMetadata MetadataConstructor() function is used to intialize a ProcessMetadata structure. The ProcessMetadata structure is a structure type used to describe a record for a Proccess. the ProcessMetadata MetadataConstructor() simply intializes a Proccess record to emphasize that the record hasn't been manipulated yet or "truly" initialized to the desired values. The MetadataConstructor() takes no parameter values and returns a record to a ProcessMetadata structure with "defaulted" values. This function is used when we first declare and initialize our ProcessMetadata record in our Main() routine

# Sectin 2.1.6:  options function
the options defaultConstructor() is used to initialize an options structure. The options structure is a structure type used to describe a record for a options.Its fields are integer types whose function is to act as a flag to determine whether an option was present when running the MYps program. the options defaultConstructor()  intializes an options record to emphasize that the options haven't been "selected" yet or "truly" initialized to the desired flag value (1 reprsents on and  -1 represents off). The options defaultConstructor() takes no parameter values and returns a record to an options structure with "defaulted" values. This function is used when we first declare and initialize our options record in our Main() routine. 


# Sectin 2.1.7:  set_Proc_Metadata function

int set_Proc_Metadata(char *Pid, options *optionStructure,  ProcessMetadata *Proc, int recursion) is a function used to intialize a record for a ProcessMetadata structure type. It checks the value of the flags in an options record and intializes the fields of a given ProcessMetadata record accordingly. The first parameter char *Pid is used to specify the PID of a proccess. The second parameter options *optionStructure takes a pointer to an options structure and its role is to check the condition of whether the specfied options records flags have been set in order to properly intialize a Process Metadata record. The third parameter ProcessMetadata *Proc takes a pointer to a ProcessMetadaata Structure and is used to initialize the fields of a a ProcessMetadata record based on whether an options record flag has been set. The fourth parameter int recursion takes an integer. Its function is to act as a flag as to whether or not the -p option has been selected or not. If it hasn't then we will use this flag variable as a condition as to manually initialize the Pid field in a ProcessMetadata record for each process we are displaying(since we arent only displaying one process now). This function is used in the DisplayProc function which is the highest level of abstraction function in the MYps.c file.


# Sectin 2.1.8:  DisplayProcInfo function

the void DisplayProcInfo(ProcessMetadata *Process, options *Myoptions) function is a function that displays the information about a process based on the specified options. The first parameter ProcessMetadata *Process, takes a pointer to ProcessMetadata structure and the second argumetn takes a pointer to an options structure. Together theres parameters are used to display the information of a ProcessMetadata record based on the values of the flags in an options record.This function is used in the DisplayProc function which is the highest level of abstraction function in the MYps.c file.

# Sectin 2.1.9:  DisplayProc function


The void dipslayProc(char *Pid, options *optionStructure,  ProcessMetadata *Proc, int recursion) is a high level abstraction function. It "is" the ps tool. it checks if "recursion is off" and sets and displays the information of one process, or if recursion is "turned on" it sets then displays the information of all proccesses by iterating through the proc filesystem, and retrieving the name of each [PID] through the help of the scandir function. Its parameters are the Sum total of the set_Proc_Metadata functions parameters, and the DisplayProcInfo functions parameters[see set_Proc_Metadata and DisplayProc functions descriptions above].


# Sectin 2.1.9.8:  uid_t uidcmp function

The uid_t uidcmp(char *path) is used to retrive the "Real_UID" of a particular process.Its parameter is a path. This path will lead to the "status" file of a particular [PID] and the function will extract the "Real_UID" field of the status file, which represents the User ID of a given process. This function returns a uid_t, which is a data type (of unsigned int) used to represent a UID.That is, this function returns the UID of a process. This function is used in the procUIDcmp function.


# # Sectin 2.1.9.9:  int procUIDcmp  function

The int procUIDcmp(char *path) function is used to to compare the real User ID of the calling process from the getuid() system call, to any process from the proc filesystem. It takes as parameter a "path" to be used when calling the uidcmp function to retrieve a spcified processes real UID. This function returns 1 if the real UID of the calling process from getuid() is the same as the real UID from the specified process from the proc filesystem or 0 if its not. This function is used in DisplayProc function as a condition as to whehter or not to print a a process if the -p option is omitted. 


 # Section 2.2: warmup.c




 # Section 2.3: Makefile 




# Section 3: Testing 
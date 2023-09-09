#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv){
    /*parse options and recieve command line arguments.
    getopt() use to pass the command line options
    loops runs untill getopt() returns -1
    switch statement value of options to determine options passed
    if unknown option passed exit from the program*/
 
    int opt_val = 0;

	while((opt_val = getopt(argc, argv, "n:hf:e")) != -1){
		switch (opt_val){
	
		case 'h':
			printf("oss [-h] [-n proc] [-s simul] [-t iter]\n\n");
            printf("proc - number of total children to launch.\n");
            printf("simul- how many children to reun simulataneously.\n");
            printf("iter -- number of pass to the worker process\n");
            printf("\n\n");
			break;
		case 'f':
			printf("This is in f \n");
			break;
		case 'e':
			printf("This is on e\n");
			break;
		default:
			return 1;

		}
    }
     
    

    
    /*
    printf("This is from oss.c\n\n");

    pid_t childPid = fork(); // This is where the child process splits from the parent

    if(childPid == 0){
        printf("I'm the chilld\n");
        printf("My Parent's PID is %d, and my PID is %d \n\n", getppid(), getpid());

        char* args[] = {"./child","Hello","there","exec","is","neat"};

        execlp("./child","./child",args[1],args[2],args[3],args[4],args[5],NULL);

        fprintf(stderr, "Exec failed, terminating");
        exit(1);
    }else{

        printf("I'm a parent! my PID is %d \n", getpid());
        printf("Now child PID %d\n\n", childPid);
        wait(0);
    }
    */
    printf("out from Parent\n");

    return 0;
}
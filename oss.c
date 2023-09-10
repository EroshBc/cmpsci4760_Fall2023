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
    int n=0;
    int s=0;
    int t=0;

	while((opt_val = getopt(argc, argv, "hn:s:t:")) != -1){ // getopt() function take arguments -n, -s ,-t
		switch (opt_val){
	
		case 'h':
            printf("******* Help Menu *******\n\n");
			printf("oss [-h] [-n proc] [-s simul] [-t iter]\n\n");
            printf("proc - number of total children to launch.\n");
            printf("simul- how many children to run simulataneously.\n");
            printf("iter -- number of pass to the worker process\n");
            printf("\n\n");
			break;
		case 'n':
            n = atoi(optarg);
			break;

		case 's':
			s = atoi(optarg);
			break;

        case 't':
			t = atoi(optarg);
			break;

		default:
            fprintf(stderr,"Invalid option entered\n");           
			exit(1);

		}
    }

    //check for non negative arguments
    if(n<=0 || s<=0 || t<=0){
        fprintf(stderr,"Invalid arguments, Please enter non negative arguments\n");           
		exit(1);
    }

     
    printf("This is from oss.c\n\n");

    pid_t childPid = fork(); // This is where the child process splits from the parent

    if(childPid == 0){
        printf("I'm the chilld\n");
      //  printf("My Parent's PID is %d, and my PID is %d \n\n", getppid(), getpid());
        printf("the value of n is %d\n", t);
        char args[10];
        sprintf(args,"%d",t);

        execl("./worker","worker",args,NULL);

        fprintf(stderr, "Exec failed, terminating");
        exit(1);
    }else{

        printf("I'm a parent! my PID is %d \n", getpid());
        printf("Now child PID %d\n\n", childPid);
        wait(0);
    }
    
    printf("out from Parent\n");

    return 0;
}
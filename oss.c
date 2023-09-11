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

    /*
    //check for non negative arguments
    if(n <= 0 || s <= 0 || t <= 0){
        fprintf(stderr,"Invalid arguments, Please enter non negative arguments\n");           
		exit(1);
    }
    */

    /* go into a loop and start doing a fork() and then an exec() call to launch worker process.
    should only do this upto simul number of times. */

    
    
   int simul_counter =0;
   
    for(int tot_chldrn=0; tot_chldrn<n;){
        
        if(simul_counter < s){
           //printf("number of sim %d\n",simul_counter+1);
           //printf("number of children %d\n",tot_chldrn+1);
            pid_t childPid = fork(); // This is where the child process splits from the parent
            
            if(childPid == 0){

                char args[2];
                sprintf(args,"%d",t);

                execl("./worker","worker",args,NULL);

                perror("exec failed\n");
                exit(1);
               

                
            }else if(childPid > 0){
              simul_counter += 1;
              tot_chldrn += 1;      
             // printf("I'm the parent. waiting for child to end \n");
            //  printf("simul is %d and tot_child %d\n",simul_counter+1,tot_chldrn+1 );
              wait(0);
              printf("**child is done...Parent ending**\n\n");
               
                
            }else{
                fprintf(stderr, "Exec failed, terminating");
                exit(1);
            }

        }else{
            //wait for child to finish
            printf("\n***child to finish***\n");

            wait(0);
            simul_counter -= 1;
            printf("this is  s %d\n",simul_counter);
        }  
    }  
    

    //wait for all remaining child process to finish
    while(simul_counter > 0){
        printf("\n***remaining child to finish***\n");
        wait(0);
        simul_counter -=1;
        
    }


    printf("out from Parent\n\n");

    return 0;
}
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    
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

    printf("out from Parent\n");

    return 0;
}
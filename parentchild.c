//using fork, wait and exec
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



int main(int argc, char * argv[]){
    printf("Hello world I have a pid of %d\n", (int) getpid());
    int new_process = fork();
    if(new_process < 0){
        fprintf(stderr, "There was an error creating the new process :(\n");
        exit(1);
    }
    
    else if(new_process == 0){
        printf("Hello, I am the newly created child with a pid of: %d\n", (int) getpid());
        // printf("Please enter 2 numbers: "\n);
         //char * myargs[4];
    char *myargs[]={"./angela",argv[1],argv[2],NULL};
    execvp(myargs[0],myargs);
    printf("This would not be printed out!\n");
    }

    else{
        int wait_process = wait(NULL);
        printf("I am parent with a pid of : %d (wc: %d)and my child has a pid of %d\n", (int) getpid(), wait_process, new_process);
        printf("Emphasis, the sum is: %d",new_process);
    }   
    return 0;
}
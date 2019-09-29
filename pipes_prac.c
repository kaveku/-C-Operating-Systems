#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    int new_process;
    int mypipefd[2];
    int ret;
    char buf[20];

    ret=pipe(mypipefd);
    if(ret==-1){
        perror("pipe");
        exit(1);
    }
    new_process=fork();
    if(new_process==0){
        /*child process */
        printf("child proces. \n");
        close(mypipefd[1]);
        read(mypipefd[0],buf,15);
        printf("buff: %s\n", buf);

    }
    else{
        /*Parent process*/
        printf("parent process: \n");
        close(mypipefd[0]);
        write(mypipefd[1],"hello there",12);
    }

}

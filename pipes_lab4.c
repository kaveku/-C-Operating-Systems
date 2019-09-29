#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char * argv[]){
    //Assuming no input value is greater than 20 characters.
    char buffer[20];
    char snum[5];
    int process1;

    //create pipe
    int mypipefd[2];
    
    //If pipe is not successfully created
     if(pipe(mypipefd)==-1){
        perror("pipe");
        exit(1);
    }

    //if pipe is successfully created.
    //Create child process
    process1=fork();

    //If new process is successfully created and returns 0 to itself
    if(process1==0){
        /*child process */
        printf("child proces. \n");
        close(mypipefd[1]);

        //Child process reading from pipe.
        read(mypipefd[0],buffer,40);

        printf("The number of Triangles in the polygon is: %s\n", buffer);
    }

    //If new process is not successfully created
    else if(process1 < 0){
        fprintf(stderr, "There was an error creating the new process :(\n");
        exit(1);
    }
    
    //If new process is successfully created and returns its pid to the parent process
    else{

        /*Parent process*/
        printf("parent process: \n");
        
        //Getting parrameters.
        int type = atoi(argv[1]);
        int length = atoi(argv[2]);
        char string_of_type[20];
        char string_of_length[20];
        snprintf (string_of_type, sizeof(string_of_type), "%d",type);

        //Converting 180 degrees to radians.
        double pi = 3.14285714286;
        double degrees=180.0/type;
        double radians=(degrees*pi)/180;
        
        //Calculating Area
        double area=(length*length*type)/type*tan(radians);
        printf("The area of the polygon is: %f \n", area);

        close(mypipefd[0]);

        //parent process Writing to pipe
        write(mypipefd[1],string_of_type,20);
        return area;
    }





}

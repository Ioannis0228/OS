#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
        pid_t pid;
        FILE *fp = fopen("outputPID.txt","w");
        if(fp == NULL){
                perror("Error opening file");
                return EXIT_FAILURE;
        }
        pid = fork();
        if(pid == -1 ){
                perror("Fork failed");
                return EXIT_FAILURE;
        }
        else if(pid == 0){
                fprintf(fp,"Child process: PID = %d\n",getpid());
        }
        else {
                fprintf(fp,"Parent process: PID = %d\n",getpid());
                wait(NULL);
        }
        if(fclose(fp) !=0){
                perror("Error closing file");
                return EXIT_FAILURE;
        }
        return 0;
}
